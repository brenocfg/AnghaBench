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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int MLX5_CAP_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_TX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL 131 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL 130 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TUNNEL_TO_L2 129 
#define  MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2 128 
 int MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX ; 
 int MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX ; 
 int /*<<< orphan*/  decap ; 
 int /*<<< orphan*/  encap_general_header ; 
 int /*<<< orphan*/  reformat_l2_to_l3_tunnel ; 
 int /*<<< orphan*/  reformat_l3_tunnel_to_l2 ; 

__attribute__((used)) static bool mlx5_ib_flow_action_packet_reformat_valid(struct mlx5_ib_dev *ibdev,
						      u8 packet_reformat_type,
						      u8 ft_type)
{
	switch (packet_reformat_type) {
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL:
		if (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX)
			return MLX5_CAP_FLOWTABLE(ibdev->mdev,
						  encap_general_header);
		break;
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL:
		if (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX)
			return MLX5_CAP_FLOWTABLE_NIC_TX(ibdev->mdev,
				reformat_l2_to_l3_tunnel);
		break;
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2:
		if (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX)
			return MLX5_CAP_FLOWTABLE_NIC_RX(ibdev->mdev,
				reformat_l3_tunnel_to_l2);
		break;
	case MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TUNNEL_TO_L2:
		if (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX)
			return MLX5_CAP_FLOWTABLE_NIC_RX(ibdev->mdev, decap);
		break;
	default:
		break;
	}

	return false;
}