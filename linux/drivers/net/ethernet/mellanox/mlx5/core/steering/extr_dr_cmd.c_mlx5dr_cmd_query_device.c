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
struct mlx5dr_cmd_caps {int /*<<< orphan*/  roce_min_src_udp; int /*<<< orphan*/  hdr_modify_icm_addr; int /*<<< orphan*/  log_icm_size; int /*<<< orphan*/  tx_sw_owner; void* max_ft_level; void* rx_sw_owner; void* nic_tx_allow_address; void* nic_tx_drop_address; void* nic_rx_drop_address; void* flex_parser_id_icmpv6_dw1; void* flex_parser_id_icmpv6_dw0; void* flex_parser_id_icmp_dw1; void* flex_parser_id_icmp_dw0; void* flex_protocols; void* gvmi; void* eswitch_manager; void* prio_tag_required; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP64_DEV_MEM (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 void* MLX5_CAP64_FLOWTABLE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_DEV_MEM (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 void* MLX5_CAP_FLOWTABLE_NIC_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_FLOWTABLE_NIC_TX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 void* MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ROCE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eswitch_manager ; 
 int /*<<< orphan*/  flex_parser_id_icmp_dw0 ; 
 int /*<<< orphan*/  flex_parser_id_icmp_dw1 ; 
 int /*<<< orphan*/  flex_parser_id_icmpv6_dw0 ; 
 int /*<<< orphan*/  flex_parser_id_icmpv6_dw1 ; 
 int /*<<< orphan*/  flex_parser_protocols ; 
 int /*<<< orphan*/  header_modify_sw_icm_start_address ; 
 int /*<<< orphan*/  log_steering_sw_icm_size ; 
 int /*<<< orphan*/  max_ft_level ; 
 scalar_t__ mlx5dr_matcher_supp_flex_parser_icmp_v4 (struct mlx5dr_cmd_caps*) ; 
 scalar_t__ mlx5dr_matcher_supp_flex_parser_icmp_v6 (struct mlx5dr_cmd_caps*) ; 
 int /*<<< orphan*/  prio_tag_required ; 
 int /*<<< orphan*/  r_roce_min_src_udp_port ; 
 int /*<<< orphan*/  sw_owner ; 
 int /*<<< orphan*/  sw_steering_nic_rx_action_drop_icm_address ; 
 int /*<<< orphan*/  sw_steering_nic_tx_action_allow_icm_address ; 
 int /*<<< orphan*/  sw_steering_nic_tx_action_drop_icm_address ; 
 int /*<<< orphan*/  vhca_id ; 

int mlx5dr_cmd_query_device(struct mlx5_core_dev *mdev,
			    struct mlx5dr_cmd_caps *caps)
{
	caps->prio_tag_required	= MLX5_CAP_GEN(mdev, prio_tag_required);
	caps->eswitch_manager	= MLX5_CAP_GEN(mdev, eswitch_manager);
	caps->gvmi		= MLX5_CAP_GEN(mdev, vhca_id);
	caps->flex_protocols	= MLX5_CAP_GEN(mdev, flex_parser_protocols);

	if (mlx5dr_matcher_supp_flex_parser_icmp_v4(caps)) {
		caps->flex_parser_id_icmp_dw0 = MLX5_CAP_GEN(mdev, flex_parser_id_icmp_dw0);
		caps->flex_parser_id_icmp_dw1 = MLX5_CAP_GEN(mdev, flex_parser_id_icmp_dw1);
	}

	if (mlx5dr_matcher_supp_flex_parser_icmp_v6(caps)) {
		caps->flex_parser_id_icmpv6_dw0 =
			MLX5_CAP_GEN(mdev, flex_parser_id_icmpv6_dw0);
		caps->flex_parser_id_icmpv6_dw1 =
			MLX5_CAP_GEN(mdev, flex_parser_id_icmpv6_dw1);
	}

	caps->nic_rx_drop_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_rx_action_drop_icm_address);
	caps->nic_tx_drop_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_tx_action_drop_icm_address);
	caps->nic_tx_allow_address =
		MLX5_CAP64_FLOWTABLE(mdev, sw_steering_nic_tx_action_allow_icm_address);

	caps->rx_sw_owner = MLX5_CAP_FLOWTABLE_NIC_RX(mdev, sw_owner);
	caps->max_ft_level = MLX5_CAP_FLOWTABLE_NIC_RX(mdev, max_ft_level);

	caps->tx_sw_owner = MLX5_CAP_FLOWTABLE_NIC_TX(mdev, sw_owner);

	caps->log_icm_size = MLX5_CAP_DEV_MEM(mdev, log_steering_sw_icm_size);
	caps->hdr_modify_icm_addr =
		MLX5_CAP64_DEV_MEM(mdev, header_modify_sw_icm_start_address);

	caps->roce_min_src_udp = MLX5_CAP_ROCE(mdev, r_roce_min_src_udp_port);

	return 0;
}