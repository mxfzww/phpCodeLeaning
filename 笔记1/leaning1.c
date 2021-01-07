//
// Created by zhaowei on 2021/1/7.
//

#include "leaning1.h"

//Zend/zend_types.h:101


typedef union _zend_value {
    zend_long         lval;				/* long value */
    double            dval;				/* double value */
    zend_refcounted  *counted;
    zend_string      *str;
    zend_array       *arr;
    zend_object      *obj;
    zend_resource    *res;
    zend_reference   *ref;
    zend_ast_ref     *ast;
    zval             *zv;
    void             *ptr;
    zend_class_entry *ce;
    zend_function    *func;
    struct {
        uint32_t w1;
        uint32_t w2;
    } ww;
} zend_value;

struct _zval_struct {
    zend_value        value;			//占8个字节
    union {
        struct {
            ZEND_ENDIAN_LOHI_4(
                    zend_uchar    type,			/* 占四个字节 */
            zend_uchar    type_flags,
                    zend_uchar    const_flags,
            zend_uchar    reserved
            )	    /* call info for EX(This) */
        } v;
        uint32_t type_info;
    } u1;
    union { //占四个字节
        uint32_t     next;                 /* hash collision chain */
        uint32_t     cache_slot;           /* literal cache slot */
        uint32_t     lineno;               /* line number (for ast nodes) */
        uint32_t     num_args;             /* arguments number for EX(This) */
        uint32_t     fe_pos;               /* foreach position */
        uint32_t     fe_iter_idx;          /* foreach iterator index */
        uint32_t     access_flags;         /* class constant access flags */
        uint32_t     property_guard;       /* single property guard */
    } u2;
};

//zvl标识php里的任意一个变量.
typedef union _zend_value {
    zend_long         lval;				/* 整形 */
    double            dval;				/* 浮点型 */
    zend_refcounted  *counted;
    zend_string      *str;              /* 字符串 */
    zend_array       *arr;                 /* 数组 */
    zend_object      *obj;
    zend_resource    *res;
    zend_reference   *ref;
    zend_ast_ref     *ast;
    zval             *zv;
    void             *ptr;
    zend_class_entry *ce;           //类
    zend_function    *func; //函数
    struct {
        uint32_t w1;
        uint32_t w2;
    } ww;
} zend_value;


//如何区分变量是什么类型
union {
    struct {
        ZEND_ENDIAN_LOHI_4(
                zend_uchar    type,			/* 占四个字节 */
        zend_uchar    type_flags, //变量类型特有的标记
                zend_uchar    const_flags, //常量类型的标记
        zend_uchar    reserved
        )	    /* call info for EX(This) */
    } v;
    uint32_t type_info;
} u1;


    type:
/* regular data types */
#define IS_UNDEF					0
#define IS_NULL						1
#define IS_FALSE					2
#define IS_TRUE						3
#define IS_LONG						4
#define IS_DOUBLE					5
#define IS_STRING					6
#define IS_ARRAY					7
#define IS_OBJECT					8
#define IS_RESOURCE					9
#define IS_REFERENCE				10


union { //占四个字节
    uint32_t     next;                 /* 数组中解决冲突使用 hash collision chain */
    uint32_t     cache_slot;           /* literal cache slot */
    uint32_t     lineno;               /* line number (for ast nodes) */
    uint32_t     num_args;             /* arguments number for EX(This) */
    uint32_t     fe_pos;               /* foreach position */
    uint32_t     fe_iter_idx;          /* foreach iterator index */
    uint32_t     access_flags;         /* class constant access flags */
    uint32_t     property_guard;       /* single property guard */
} u2;


//zvl 有三个联合体 value u1 和 u2

//value 的类型 是由 u1的 type决定的.


//通过echo 可以在zend虚拟机里打个断点.  b ZEND_ECHO_SPEC_CV_HANDLER



/*
        $a = 2;

echo $a;

$b = "fdsafa";

echo $b;

$c = new stdclass();

echo $c;

$e = [1,3,213,214,21];

echo $e;

$f = null;

echo $f;

$g = false;

echo $g;

$h =true;

echo $h;*/


//这几个变量都是相隔16个字节 , 放在了一起, 相当于每个变量占用了一个zvl