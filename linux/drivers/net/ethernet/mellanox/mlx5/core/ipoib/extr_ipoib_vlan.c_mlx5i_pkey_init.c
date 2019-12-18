#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct mlx5e_profile {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  log_rq_mtu_frames; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int mlx5i_init (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,void*) ; 
 int /*<<< orphan*/  mlx5i_pkey_ethtool_ops ; 
 int /*<<< orphan*/  mlx5i_pkey_netdev_ops ; 

__attribute__((used)) static int mlx5i_pkey_init(struct mlx5_core_dev *mdev,
			   struct net_device *netdev,
			   const struct mlx5e_profile *profile,
			   void *ppriv)
{
	struct mlx5e_priv *priv  = mlx5i_epriv(netdev);
	int err;

	err = mlx5i_init(mdev, netdev, profile, ppriv);
	if (err)
		return err;

	/* Override parent ndo */
	netdev->netdev_ops = &mlx5i_pkey_netdev_ops;

	/* Set child limited ethtool support */
	netdev->ethtool_ops = &mlx5i_pkey_ethtool_ops;

	/* Use dummy rqs */
	priv->channels.params.log_rq_mtu_frames = MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE;

	return 0;
}