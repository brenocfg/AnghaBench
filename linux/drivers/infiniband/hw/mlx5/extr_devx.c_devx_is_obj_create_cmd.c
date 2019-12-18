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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
#define  MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT 156 
#define  MLX5_CMD_OP_ALLOC_FLOW_COUNTER 155 
#define  MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT 154 
#define  MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT 153 
#define  MLX5_CMD_OP_ALLOC_PD 152 
#define  MLX5_CMD_OP_ALLOC_Q_COUNTER 151 
#define  MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN 150 
#define  MLX5_CMD_OP_ALLOC_XRCD 149 
#define  MLX5_CMD_OP_ATTACH_TO_MCG 148 
#define  MLX5_CMD_OP_CREATE_CQ 147 
#define  MLX5_CMD_OP_CREATE_DCT 146 
#define  MLX5_CMD_OP_CREATE_FLOW_GROUP 145 
#define  MLX5_CMD_OP_CREATE_FLOW_TABLE 144 
#define  MLX5_CMD_OP_CREATE_GENERAL_OBJECT 143 
#define  MLX5_CMD_OP_CREATE_MKEY 142 
#define  MLX5_CMD_OP_CREATE_PSV 141 
#define  MLX5_CMD_OP_CREATE_QP 140 
#define  MLX5_CMD_OP_CREATE_RMP 139 
#define  MLX5_CMD_OP_CREATE_RQ 138 
#define  MLX5_CMD_OP_CREATE_RQT 137 
#define  MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT 136 
#define  MLX5_CMD_OP_CREATE_SQ 135 
#define  MLX5_CMD_OP_CREATE_SRQ 134 
#define  MLX5_CMD_OP_CREATE_TIR 133 
#define  MLX5_CMD_OP_CREATE_TIS 132 
#define  MLX5_CMD_OP_CREATE_XRC_SRQ 131 
#define  MLX5_CMD_OP_CREATE_XRQ 130 
#define  MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY 129 
#define  MLX5_CMD_OP_SET_L2_TABLE_ENTRY 128 
 int MLX5_GET (int /*<<< orphan*/ ,void const*,int*) ; 
 int /*<<< orphan*/  create_psv_in ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int num_psv ; 
 int op_mod ; 
 int /*<<< orphan*/  set_fte_in ; 

__attribute__((used)) static bool devx_is_obj_create_cmd(const void *in, u16 *opcode)
{
	*opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (*opcode) {
	case MLX5_CMD_OP_CREATE_GENERAL_OBJECT:
	case MLX5_CMD_OP_CREATE_MKEY:
	case MLX5_CMD_OP_CREATE_CQ:
	case MLX5_CMD_OP_ALLOC_PD:
	case MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN:
	case MLX5_CMD_OP_CREATE_RMP:
	case MLX5_CMD_OP_CREATE_SQ:
	case MLX5_CMD_OP_CREATE_RQ:
	case MLX5_CMD_OP_CREATE_RQT:
	case MLX5_CMD_OP_CREATE_TIR:
	case MLX5_CMD_OP_CREATE_TIS:
	case MLX5_CMD_OP_ALLOC_Q_COUNTER:
	case MLX5_CMD_OP_CREATE_FLOW_TABLE:
	case MLX5_CMD_OP_CREATE_FLOW_GROUP:
	case MLX5_CMD_OP_ALLOC_FLOW_COUNTER:
	case MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT:
	case MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT:
	case MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT:
	case MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
	case MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
	case MLX5_CMD_OP_CREATE_QP:
	case MLX5_CMD_OP_CREATE_SRQ:
	case MLX5_CMD_OP_CREATE_XRC_SRQ:
	case MLX5_CMD_OP_CREATE_DCT:
	case MLX5_CMD_OP_CREATE_XRQ:
	case MLX5_CMD_OP_ATTACH_TO_MCG:
	case MLX5_CMD_OP_ALLOC_XRCD:
		return true;
	case MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
	{
		u16 op_mod = MLX5_GET(set_fte_in, in, op_mod);
		if (op_mod == 0)
			return true;
		return false;
	}
	case MLX5_CMD_OP_CREATE_PSV:
	{
		u8 num_psv = MLX5_GET(create_psv_in, in, num_psv);

		if (num_psv == 1)
			return true;
		return false;
	}
	default:
		return false;
	}
}