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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/ * tlsdev_ops; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct net_device* netdev; } ;

/* Variables and functions */
 int MLX5_ACCEL_TLS_LRO ; 
 int MLX5_ACCEL_TLS_RX ; 
 int MLX5_ACCEL_TLS_TX ; 
 int /*<<< orphan*/  NETIF_F_HW_TLS_RX ; 
 int /*<<< orphan*/  NETIF_F_HW_TLS_TX ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 scalar_t__ mlx5_accel_is_ktls_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_accel_is_tls_device (int /*<<< orphan*/ ) ; 
 int mlx5_accel_tls_device_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_ktls_build_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_tls_ops ; 

void mlx5e_tls_build_netdev(struct mlx5e_priv *priv)
{
	struct net_device *netdev = priv->netdev;
	u32 caps;

	if (mlx5_accel_is_ktls_device(priv->mdev)) {
		mlx5e_ktls_build_netdev(priv);
		return;
	}

	if (!mlx5_accel_is_tls_device(priv->mdev))
		return;

	caps = mlx5_accel_tls_device_caps(priv->mdev);
	if (caps & MLX5_ACCEL_TLS_TX) {
		netdev->features          |= NETIF_F_HW_TLS_TX;
		netdev->hw_features       |= NETIF_F_HW_TLS_TX;
	}

	if (caps & MLX5_ACCEL_TLS_RX) {
		netdev->features          |= NETIF_F_HW_TLS_RX;
		netdev->hw_features       |= NETIF_F_HW_TLS_RX;
	}

	if (!(caps & MLX5_ACCEL_TLS_LRO)) {
		netdev->features          &= ~NETIF_F_LRO;
		netdev->hw_features       &= ~NETIF_F_LRO;
	}

	netdev->tlsdev_ops = &mlx5e_tls_ops;
}