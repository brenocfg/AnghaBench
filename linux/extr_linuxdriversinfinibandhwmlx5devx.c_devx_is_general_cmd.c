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
#define  MLX5_CMD_OP_GET_DROPPED_PACKET_LOG 140 
#define  MLX5_CMD_OP_NOP 139 
#define  MLX5_CMD_OP_QUERY_ADAPTER 138 
#define  MLX5_CMD_OP_QUERY_CONG_PARAMS 137 
#define  MLX5_CMD_OP_QUERY_CONG_STATISTICS 136 
#define  MLX5_CMD_OP_QUERY_CONG_STATUS 135 
#define  MLX5_CMD_OP_QUERY_HCA_CAP 134 
#define  MLX5_CMD_OP_QUERY_ISSI 133 
#define  MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT 132 
#define  MLX5_CMD_OP_QUERY_ROCE_ADDRESS 131 
#define  MLX5_CMD_OP_QUERY_VNIC_ENV 130 
#define  MLX5_CMD_OP_QUERY_VPORT_COUNTER 129 
#define  MLX5_CMD_OP_QUERY_VPORT_STATE 128 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int opcode ; 

__attribute__((used)) static bool devx_is_general_cmd(void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (opcode) {
	case MLX5_CMD_OP_QUERY_HCA_CAP:
	case MLX5_CMD_OP_QUERY_VPORT_STATE:
	case MLX5_CMD_OP_QUERY_ADAPTER:
	case MLX5_CMD_OP_QUERY_ISSI:
	case MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT:
	case MLX5_CMD_OP_QUERY_ROCE_ADDRESS:
	case MLX5_CMD_OP_QUERY_VNIC_ENV:
	case MLX5_CMD_OP_QUERY_VPORT_COUNTER:
	case MLX5_CMD_OP_GET_DROPPED_PACKET_LOG:
	case MLX5_CMD_OP_NOP:
	case MLX5_CMD_OP_QUERY_CONG_STATUS:
	case MLX5_CMD_OP_QUERY_CONG_PARAMS:
	case MLX5_CMD_OP_QUERY_CONG_STATISTICS:
		return true;
	default:
		return false;
	}
}