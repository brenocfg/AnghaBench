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
#define  MLX5_CMD_OP_2ERR_QP 152 
#define  MLX5_CMD_OP_2RST_QP 151 
#define  MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT 150 
#define  MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION 149 
#define  MLX5_CMD_OP_ARM_RQ 148 
#define  MLX5_CMD_OP_ARM_XRC_SRQ 147 
#define  MLX5_CMD_OP_ARM_XRQ 146 
#define  MLX5_CMD_OP_DRAIN_DCT 145 
#define  MLX5_CMD_OP_INIT2RTR_QP 144 
#define  MLX5_CMD_OP_MODIFY_CQ 143 
#define  MLX5_CMD_OP_MODIFY_FLOW_TABLE 142 
#define  MLX5_CMD_OP_MODIFY_GENERAL_OBJECT 141 
#define  MLX5_CMD_OP_MODIFY_RMP 140 
#define  MLX5_CMD_OP_MODIFY_RQ 139 
#define  MLX5_CMD_OP_MODIFY_RQT 138 
#define  MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT 137 
#define  MLX5_CMD_OP_MODIFY_SQ 136 
#define  MLX5_CMD_OP_MODIFY_TIR 135 
#define  MLX5_CMD_OP_MODIFY_TIS 134 
#define  MLX5_CMD_OP_RST2INIT_QP 133 
#define  MLX5_CMD_OP_RTR2RTS_QP 132 
#define  MLX5_CMD_OP_RTS2RTS_QP 131 
#define  MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY 130 
#define  MLX5_CMD_OP_SET_L2_TABLE_ENTRY 129 
#define  MLX5_CMD_OP_SQERR2RTS_QP 128 
 int MLX5_GET (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int op_mod ; 
 int opcode ; 
 int /*<<< orphan*/  set_fte_in ; 

__attribute__((used)) static bool devx_is_obj_modify_cmd(const void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (opcode) {
	case MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	case MLX5_CMD_OP_MODIFY_CQ:
	case MLX5_CMD_OP_MODIFY_RMP:
	case MLX5_CMD_OP_MODIFY_SQ:
	case MLX5_CMD_OP_MODIFY_RQ:
	case MLX5_CMD_OP_MODIFY_RQT:
	case MLX5_CMD_OP_MODIFY_TIR:
	case MLX5_CMD_OP_MODIFY_TIS:
	case MLX5_CMD_OP_MODIFY_FLOW_TABLE:
	case MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
	case MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
	case MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
	case MLX5_CMD_OP_RST2INIT_QP:
	case MLX5_CMD_OP_INIT2RTR_QP:
	case MLX5_CMD_OP_RTR2RTS_QP:
	case MLX5_CMD_OP_RTS2RTS_QP:
	case MLX5_CMD_OP_SQERR2RTS_QP:
	case MLX5_CMD_OP_2ERR_QP:
	case MLX5_CMD_OP_2RST_QP:
	case MLX5_CMD_OP_ARM_XRC_SRQ:
	case MLX5_CMD_OP_ARM_RQ:
	case MLX5_CMD_OP_DRAIN_DCT:
	case MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
	case MLX5_CMD_OP_ARM_XRQ:
		return true;
	case MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
	{
		u16 op_mod = MLX5_GET(set_fte_in, in, op_mod);

		if (op_mod == 1)
			return true;
		return false;
	}
	default:
		return false;
	}
}