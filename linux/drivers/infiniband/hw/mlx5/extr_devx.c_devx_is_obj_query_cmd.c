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
#define  MLX5_CMD_OP_QUERY_CQ 152 
#define  MLX5_CMD_OP_QUERY_DCT 151 
#define  MLX5_CMD_OP_QUERY_FLOW_COUNTER 150 
#define  MLX5_CMD_OP_QUERY_FLOW_GROUP 149 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE 148 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY 147 
#define  MLX5_CMD_OP_QUERY_GENERAL_OBJECT 146 
#define  MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY 145 
#define  MLX5_CMD_OP_QUERY_MKEY 144 
#define  MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT 143 
#define  MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT 142 
#define  MLX5_CMD_OP_QUERY_QP 141 
#define  MLX5_CMD_OP_QUERY_Q_COUNTER 140 
#define  MLX5_CMD_OP_QUERY_RMP 139 
#define  MLX5_CMD_OP_QUERY_RQ 138 
#define  MLX5_CMD_OP_QUERY_RQT 137 
#define  MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT 136 
#define  MLX5_CMD_OP_QUERY_SQ 135 
#define  MLX5_CMD_OP_QUERY_SRQ 134 
#define  MLX5_CMD_OP_QUERY_TIR 133 
#define  MLX5_CMD_OP_QUERY_TIS 132 
#define  MLX5_CMD_OP_QUERY_XRC_SRQ 131 
#define  MLX5_CMD_OP_QUERY_XRQ 130 
#define  MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY 129 
#define  MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS 128 
 int MLX5_GET (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int opcode ; 

__attribute__((used)) static bool devx_is_obj_query_cmd(const void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (opcode) {
	case MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
	case MLX5_CMD_OP_QUERY_MKEY:
	case MLX5_CMD_OP_QUERY_CQ:
	case MLX5_CMD_OP_QUERY_RMP:
	case MLX5_CMD_OP_QUERY_SQ:
	case MLX5_CMD_OP_QUERY_RQ:
	case MLX5_CMD_OP_QUERY_RQT:
	case MLX5_CMD_OP_QUERY_TIR:
	case MLX5_CMD_OP_QUERY_TIS:
	case MLX5_CMD_OP_QUERY_Q_COUNTER:
	case MLX5_CMD_OP_QUERY_FLOW_TABLE:
	case MLX5_CMD_OP_QUERY_FLOW_GROUP:
	case MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
	case MLX5_CMD_OP_QUERY_FLOW_COUNTER:
	case MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT:
	case MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
	case MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
	case MLX5_CMD_OP_QUERY_QP:
	case MLX5_CMD_OP_QUERY_SRQ:
	case MLX5_CMD_OP_QUERY_XRC_SRQ:
	case MLX5_CMD_OP_QUERY_DCT:
	case MLX5_CMD_OP_QUERY_XRQ:
	case MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY:
	case MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS:
	case MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT:
		return true;
	default:
		return false;
	}
}