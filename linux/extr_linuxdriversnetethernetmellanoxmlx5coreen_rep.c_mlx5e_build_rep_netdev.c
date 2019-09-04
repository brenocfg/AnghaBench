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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int watchdog_timeo; int features; int hw_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * switchdev_ops; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {TYPE_1__ channels; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int HZ ; 
 int /*<<< orphan*/  MLX5E_HW2SW_MTU (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETIF_F_HW_TC ; 
 int NETIF_F_NETNS_LOCAL ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  mlx5_query_port_max_mtu (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_netdev_ops_rep ; 
 int /*<<< orphan*/  mlx5e_rep_ethtool_ops ; 
 int /*<<< orphan*/  mlx5e_rep_switchdev_ops ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_build_rep_netdev(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	u16 max_mtu;

	netdev->netdev_ops = &mlx5e_netdev_ops_rep;

	netdev->watchdog_timeo    = 15 * HZ;

	netdev->ethtool_ops	  = &mlx5e_rep_ethtool_ops;

	netdev->switchdev_ops = &mlx5e_rep_switchdev_ops;

	netdev->features	 |= NETIF_F_VLAN_CHALLENGED | NETIF_F_HW_TC | NETIF_F_NETNS_LOCAL;
	netdev->hw_features      |= NETIF_F_HW_TC;

	eth_hw_addr_random(netdev);

	netdev->min_mtu = ETH_MIN_MTU;
	mlx5_query_port_max_mtu(mdev, &max_mtu, 1);
	netdev->max_mtu = MLX5E_HW2SW_MTU(&priv->channels.params, max_mtu);
}