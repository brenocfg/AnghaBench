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
struct net_device {int /*<<< orphan*/ * tlsdev_ops; int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_TLS_TX ; 
 int /*<<< orphan*/  mlx5_accel_is_ktls_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_ktls_ops ; 

void mlx5e_ktls_build_netdev(struct mlx5e_priv *priv)
{
	struct net_device *netdev = priv->netdev;

	if (!mlx5_accel_is_ktls_device(priv->mdev))
		return;

	netdev->hw_features |= NETIF_F_HW_TLS_TX;
	netdev->features    |= NETIF_F_HW_TLS_TX;

	netdev->tlsdev_ops = &mlx5e_ktls_ops;
}