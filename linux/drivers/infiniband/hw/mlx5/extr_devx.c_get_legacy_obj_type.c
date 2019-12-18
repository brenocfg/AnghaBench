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

/* Variables and functions */
#define  MLX5_CMD_OP_CREATE_DCT 131 
#define  MLX5_CMD_OP_CREATE_QP 130 
#define  MLX5_CMD_OP_CREATE_RQ 129 
#define  MLX5_CMD_OP_CREATE_SQ 128 
 int MLX5_EVENT_QUEUE_TYPE_DCT ; 
 int MLX5_EVENT_QUEUE_TYPE_QP ; 
 int MLX5_EVENT_QUEUE_TYPE_RQ ; 
 int MLX5_EVENT_QUEUE_TYPE_SQ ; 

__attribute__((used)) static u16 get_legacy_obj_type(u16 opcode)
{
	switch (opcode) {
	case MLX5_CMD_OP_CREATE_RQ:
		return MLX5_EVENT_QUEUE_TYPE_RQ;
	case MLX5_CMD_OP_CREATE_QP:
		return MLX5_EVENT_QUEUE_TYPE_QP;
	case MLX5_CMD_OP_CREATE_SQ:
		return MLX5_EVENT_QUEUE_TYPE_SQ;
	case MLX5_CMD_OP_CREATE_DCT:
		return MLX5_EVENT_QUEUE_TYPE_DCT;
	default:
		return 0;
	}
}