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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_GENERAL_END ; 
 int MLX5_CMD_OP_GENERAL_START ; 
#define  MLX5_CMD_OP_GET_DROPPED_PACKET_LOG 143 
#define  MLX5_CMD_OP_NOP 142 
#define  MLX5_CMD_OP_QUERY_ADAPTER 141 
#define  MLX5_CMD_OP_QUERY_CONG_PARAMS 140 
#define  MLX5_CMD_OP_QUERY_CONG_STATISTICS 139 
#define  MLX5_CMD_OP_QUERY_CONG_STATUS 138 
#define  MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT 137 
#define  MLX5_CMD_OP_QUERY_HCA_CAP 136 
#define  MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT 135 
#define  MLX5_CMD_OP_QUERY_ISSI 134 
#define  MLX5_CMD_OP_QUERY_LAG 133 
#define  MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT 132 
#define  MLX5_CMD_OP_QUERY_ROCE_ADDRESS 131 
#define  MLX5_CMD_OP_QUERY_VNIC_ENV 130 
#define  MLX5_CMD_OP_QUERY_VPORT_COUNTER 129 
#define  MLX5_CMD_OP_QUERY_VPORT_STATE 128 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int opcode ; 
 int /*<<< orphan*/  vhca_tunnel_commands ; 
 int /*<<< orphan*/  vhca_tunnel_id ; 

__attribute__((used)) static bool devx_is_general_cmd(void *in, struct mlx5_ib_dev *dev)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	/* Pass all cmds for vhca_tunnel as general, tracking is done in FW */
	if ((MLX5_CAP_GEN_64(dev->mdev, vhca_tunnel_commands) &&
	     MLX5_GET(general_obj_in_cmd_hdr, in, vhca_tunnel_id)) ||
	    (opcode >= MLX5_CMD_OP_GENERAL_START &&
	     opcode < MLX5_CMD_OP_GENERAL_END))
		return true;

	switch (opcode) {
	case MLX5_CMD_OP_QUERY_HCA_CAP:
	case MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT:
	case MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT:
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
	case MLX5_CMD_OP_QUERY_LAG:
		return true;
	default:
		return false;
	}
}