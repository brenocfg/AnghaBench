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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx5e_profile {int /*<<< orphan*/  (* max_nch ) (struct mlx5_core_dev*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {int max_opened_tc; int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  tx_timeout_work; int /*<<< orphan*/  set_rx_mode_work; int /*<<< orphan*/  update_carrier_work; int /*<<< orphan*/  state_lock; TYPE_1__ channels; int /*<<< orphan*/  msglevel; void* ppriv; struct mlx5e_profile const* profile; struct net_device* netdev; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_MSG_LEVEL ; 
 int /*<<< orphan*/  mlx5e_build_nic_params (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_set_rx_mode_work ; 
 int /*<<< orphan*/  mlx5e_timestamp_init (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_tx_timeout_work ; 
 int /*<<< orphan*/  mlx5e_update_carrier_work ; 
 int /*<<< orphan*/  mlx5e_update_stats_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5e_build_nic_netdev_priv(struct mlx5_core_dev *mdev,
					struct net_device *netdev,
					const struct mlx5e_profile *profile,
					void *ppriv)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	priv->mdev        = mdev;
	priv->netdev      = netdev;
	priv->profile     = profile;
	priv->ppriv       = ppriv;
	priv->msglevel    = MLX5E_MSG_LEVEL;
	priv->max_opened_tc = 1;

	mlx5e_build_nic_params(mdev, &priv->channels.params,
			       profile->max_nch(mdev), netdev->mtu);

	mutex_init(&priv->state_lock);

	INIT_WORK(&priv->update_carrier_work, mlx5e_update_carrier_work);
	INIT_WORK(&priv->set_rx_mode_work, mlx5e_set_rx_mode_work);
	INIT_WORK(&priv->tx_timeout_work, mlx5e_tx_timeout_work);
	INIT_DELAYED_WORK(&priv->update_stats_work, mlx5e_update_stats_work);

	mlx5e_timestamp_init(priv);
}