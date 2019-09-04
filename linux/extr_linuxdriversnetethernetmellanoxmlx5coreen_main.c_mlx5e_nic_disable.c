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
struct mlx5e_priv {struct mlx5_core_dev* mdev; int /*<<< orphan*/  set_rx_mode_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  netdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_lag_remove (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_disable_async_events (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_unregister_vport_reps (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void mlx5e_nic_disable(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;

#ifdef CONFIG_MLX5_CORE_EN_DCB
	if (priv->netdev->reg_state == NETREG_REGISTERED)
		mlx5e_dcbnl_delete_app(priv);
#endif

	rtnl_lock();
	if (netif_running(priv->netdev))
		mlx5e_close(priv->netdev);
	netif_device_detach(priv->netdev);
	rtnl_unlock();

	queue_work(priv->wq, &priv->set_rx_mode_work);

	if (MLX5_ESWITCH_MANAGER(priv->mdev))
		mlx5e_unregister_vport_reps(priv);

	mlx5e_disable_async_events(priv);
	mlx5_lag_remove(mdev);
}