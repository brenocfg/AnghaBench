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
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  state; int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  wq; TYPE_1__* profile; int /*<<< orphan*/  channels; } ;
struct TYPE_2__ {scalar_t__ update_stats; int /*<<< orphan*/  (* update_carrier ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_priv_channels (struct mlx5e_priv*) ; 
 int mlx5e_open_channels (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_refresh_tirs (struct mlx5e_priv*,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

int mlx5e_open_locked(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err;

	set_bit(MLX5E_STATE_OPENED, &priv->state);

	err = mlx5e_open_channels(priv, &priv->channels);
	if (err)
		goto err_clear_state_opened_flag;

	mlx5e_refresh_tirs(priv, false);
	mlx5e_activate_priv_channels(priv);
	if (priv->profile->update_carrier)
		priv->profile->update_carrier(priv);

	if (priv->profile->update_stats)
		queue_delayed_work(priv->wq, &priv->update_stats_work, 0);

	return 0;

err_clear_state_opened_flag:
	clear_bit(MLX5E_STATE_OPENED, &priv->state);
	return err;
}