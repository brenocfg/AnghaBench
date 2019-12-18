#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct devx_obj {int obj_id; } ;

/* Variables and functions */
#define  MLX5_CMD_OP_ALLOC_FLOW_COUNTER 142 
#define  MLX5_CMD_OP_CREATE_CQ 141 
#define  MLX5_CMD_OP_CREATE_DCT 140 
#define  MLX5_CMD_OP_CREATE_GENERAL_OBJECT 139 
#define  MLX5_CMD_OP_CREATE_PSV 138 
#define  MLX5_CMD_OP_CREATE_QP 137 
#define  MLX5_CMD_OP_CREATE_RMP 136 
#define  MLX5_CMD_OP_CREATE_RQ 135 
#define  MLX5_CMD_OP_CREATE_RQT 134 
#define  MLX5_CMD_OP_CREATE_SQ 133 
#define  MLX5_CMD_OP_CREATE_TIR 132 
#define  MLX5_CMD_OP_CREATE_TIS 131 
#define  MLX5_CMD_OP_CREATE_XRC_SRQ 130 
#define  MLX5_CMD_OP_CREATE_XRQ 129 
 int MLX5_OBJ_TYPE_CQ ; 
 int MLX5_OBJ_TYPE_DCT ; 
 int MLX5_OBJ_TYPE_FLOW_COUNTER ; 
#define  MLX5_OBJ_TYPE_MKEY 128 
 int MLX5_OBJ_TYPE_PSV ; 
 int MLX5_OBJ_TYPE_QP ; 
 int MLX5_OBJ_TYPE_RMP ; 
 int MLX5_OBJ_TYPE_RQ ; 
 int MLX5_OBJ_TYPE_RQT ; 
 int MLX5_OBJ_TYPE_SQ ; 
 int MLX5_OBJ_TYPE_TIR ; 
 int MLX5_OBJ_TYPE_TIS ; 
 int MLX5_OBJ_TYPE_XRC_SRQ ; 
 int MLX5_OBJ_TYPE_XRQ ; 
 int get_legacy_obj_type (int) ; 
 scalar_t__ is_legacy_obj_event_num (int) ; 

__attribute__((used)) static u16 get_dec_obj_type(struct devx_obj *obj, u16 event_num)
{
	u16 opcode;

	opcode = (obj->obj_id >> 32) & 0xffff;

	if (is_legacy_obj_event_num(event_num))
		return get_legacy_obj_type(opcode);

	switch (opcode) {
	case MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
		return (obj->obj_id >> 48);
	case MLX5_CMD_OP_CREATE_RQ:
		return MLX5_OBJ_TYPE_RQ;
	case MLX5_CMD_OP_CREATE_QP:
		return MLX5_OBJ_TYPE_QP;
	case MLX5_CMD_OP_CREATE_SQ:
		return MLX5_OBJ_TYPE_SQ;
	case MLX5_CMD_OP_CREATE_DCT:
		return MLX5_OBJ_TYPE_DCT;
	case MLX5_CMD_OP_CREATE_TIR:
		return MLX5_OBJ_TYPE_TIR;
	case MLX5_CMD_OP_CREATE_TIS:
		return MLX5_OBJ_TYPE_TIS;
	case MLX5_CMD_OP_CREATE_PSV:
		return MLX5_OBJ_TYPE_PSV;
	case MLX5_OBJ_TYPE_MKEY:
		return MLX5_OBJ_TYPE_MKEY;
	case MLX5_CMD_OP_CREATE_RMP:
		return MLX5_OBJ_TYPE_RMP;
	case MLX5_CMD_OP_CREATE_XRC_SRQ:
		return MLX5_OBJ_TYPE_XRC_SRQ;
	case MLX5_CMD_OP_CREATE_XRQ:
		return MLX5_OBJ_TYPE_XRQ;
	case MLX5_CMD_OP_CREATE_RQT:
		return MLX5_OBJ_TYPE_RQT;
	case MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
		return MLX5_OBJ_TYPE_FLOW_COUNTER;
	case MLX5_CMD_OP_CREATE_CQ:
		return MLX5_OBJ_TYPE_CQ;
	default:
		return 0;
	}
}