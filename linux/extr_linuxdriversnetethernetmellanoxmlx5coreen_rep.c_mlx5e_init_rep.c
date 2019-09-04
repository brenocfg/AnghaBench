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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx5e_profile {int /*<<< orphan*/  (* max_nch ) (struct mlx5_core_dev*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  num_channels; } ;
struct TYPE_3__ {TYPE_2__ params; } ;
struct mlx5e_priv {TYPE_1__ channels; int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  state_lock; void* ppriv; struct mlx5e_profile const* profile; struct net_device* netdev; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_rep_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_build_rep_params (struct mlx5_core_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_timestamp_init (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_update_stats_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5e_init_rep(struct mlx5_core_dev *mdev,
			   struct net_device *netdev,
			   const struct mlx5e_profile *profile,
			   void *ppriv)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	priv->mdev                         = mdev;
	priv->netdev                       = netdev;
	priv->profile                      = profile;
	priv->ppriv                        = ppriv;

	mutex_init(&priv->state_lock);

	INIT_DELAYED_WORK(&priv->update_stats_work, mlx5e_update_stats_work);

	priv->channels.params.num_channels = profile->max_nch(mdev);

	mlx5e_build_rep_params(mdev, &priv->channels.params, netdev->mtu);
	mlx5e_build_rep_netdev(netdev);

	mlx5e_timestamp_init(priv);
}