#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_ft_level; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  cq_moderation ; 
 int /*<<< orphan*/  csum_cap ; 
 int /*<<< orphan*/  eth_net_offloads ; 
 TYPE_1__ flow_table_properties_nic_receive ; 
 int /*<<< orphan*/  max_lso_cap ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  nic_flow_table ; 
 int /*<<< orphan*/  port_type ; 
 int /*<<< orphan*/  rss_ind_tbl_cap ; 
 int /*<<< orphan*/  self_lb_en_modifiable ; 
 int /*<<< orphan*/  vlan_cap ; 

__attribute__((used)) static int mlx5e_check_required_hca_cap(struct mlx5_core_dev *mdev)
{
	if (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		return -EOPNOTSUPP;
	if (!MLX5_CAP_GEN(mdev, eth_net_offloads) ||
	    !MLX5_CAP_GEN(mdev, nic_flow_table) ||
	    !MLX5_CAP_ETH(mdev, csum_cap) ||
	    !MLX5_CAP_ETH(mdev, max_lso_cap) ||
	    !MLX5_CAP_ETH(mdev, vlan_cap) ||
	    !MLX5_CAP_ETH(mdev, rss_ind_tbl_cap) ||
	    MLX5_CAP_FLOWTABLE(mdev,
			       flow_table_properties_nic_receive.max_ft_level)
			       < 3) {
		mlx5_core_warn(mdev,
			       "Not creating net device, some required device capabilities are missing\n");
		return -EOPNOTSUPP;
	}
	if (!MLX5_CAP_ETH(mdev, self_lb_en_modifiable))
		mlx5_core_warn(mdev, "Self loop back prevention is not supported\n");
	if (!MLX5_CAP_GEN(mdev, cq_moderation))
		mlx5_core_warn(mdev, "CQ moderation is not supported\n");

	return 0;
}