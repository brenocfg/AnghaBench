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
struct net_device {int /*<<< orphan*/  hw_enc_features; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/ * xfrmdev_ops; } ;
struct mlx5e_priv {int /*<<< orphan*/  ipsec; struct net_device* netdev; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_ACCEL_IPSEC_CAP_ESP ; 
 int MLX5_ACCEL_IPSEC_CAP_LSO ; 
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_F_GSO_ESP ; 
 int /*<<< orphan*/  NETIF_F_HW_ESP ; 
 int /*<<< orphan*/  NETIF_F_HW_ESP_TX_CSUM ; 
 int mlx5_accel_ipsec_device_caps (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_xfrmdev_ops ; 
 int /*<<< orphan*/  swp ; 
 int /*<<< orphan*/  swp_csum ; 
 int /*<<< orphan*/  swp_lso ; 

void mlx5e_ipsec_build_netdev(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	struct net_device *netdev = priv->netdev;

	if (!priv->ipsec)
		return;

	if (!(mlx5_accel_ipsec_device_caps(mdev) & MLX5_ACCEL_IPSEC_CAP_ESP) ||
	    !MLX5_CAP_ETH(mdev, swp)) {
		mlx5_core_dbg(mdev, "mlx5e: ESP and SWP offload not supported\n");
		return;
	}

	mlx5_core_info(mdev, "mlx5e: IPSec ESP acceleration enabled\n");
	netdev->xfrmdev_ops = &mlx5e_ipsec_xfrmdev_ops;
	netdev->features |= NETIF_F_HW_ESP;
	netdev->hw_enc_features |= NETIF_F_HW_ESP;

	if (!MLX5_CAP_ETH(mdev, swp_csum)) {
		mlx5_core_dbg(mdev, "mlx5e: SWP checksum not supported\n");
		return;
	}

	netdev->features |= NETIF_F_HW_ESP_TX_CSUM;
	netdev->hw_enc_features |= NETIF_F_HW_ESP_TX_CSUM;

	if (!(mlx5_accel_ipsec_device_caps(mdev) & MLX5_ACCEL_IPSEC_CAP_LSO) ||
	    !MLX5_CAP_ETH(mdev, swp_lso)) {
		mlx5_core_dbg(mdev, "mlx5e: ESP LSO not supported\n");
		return;
	}

	mlx5_core_dbg(mdev, "mlx5e: ESP GSO capability turned on\n");
	netdev->features |= NETIF_F_GSO_ESP;
	netdev->hw_features |= NETIF_F_GSO_ESP;
	netdev->hw_enc_features |= NETIF_F_GSO_ESP;
}