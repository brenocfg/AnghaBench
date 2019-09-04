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
struct net_device {int dummy; } ;
struct mlx5e_priv {struct net_device* netdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_mdev_resources (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_detach_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 

__attribute__((used)) static void mlx5e_detach(struct mlx5_core_dev *mdev, void *vpriv)
{
	struct mlx5e_priv *priv = vpriv;
	struct net_device *netdev = priv->netdev;

	if (!netif_device_present(netdev))
		return;

	mlx5e_detach_netdev(priv);
	mlx5e_destroy_mdev_resources(mdev);
}