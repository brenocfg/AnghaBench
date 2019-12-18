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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_query_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vport_group_manager ; 

__attribute__((used)) static void mlx5e_set_netdev_dev_addr(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	mlx5_query_mac_address(priv->mdev, netdev->dev_addr);
	if (is_zero_ether_addr(netdev->dev_addr) &&
	    !MLX5_CAP_GEN(priv->mdev, vport_group_manager)) {
		eth_hw_addr_random(netdev);
		mlx5_core_info(priv->mdev, "Assigned random MAC address %pM\n", netdev->dev_addr);
	}
}