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
struct TYPE_2__ {int /*<<< orphan*/  reoffload_flows_work; } ;
struct mlx5e_rep_priv {TYPE_1__ uplink_priv; } ;
struct mlx5e_priv {int /*<<< orphan*/  events_nb; struct mlx5e_rep_priv* ppriv; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_lag_remove (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_dcbnl_delete_app (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_uplink_rep_disable(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;

#ifdef CONFIG_MLX5_CORE_EN_DCB
	mlx5e_dcbnl_delete_app(priv);
#endif
	mlx5_notifier_unregister(mdev, &priv->events_nb);
	cancel_work_sync(&rpriv->uplink_priv.reoffload_flows_work);
	mlx5_lag_remove(mdev);
}