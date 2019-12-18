#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int xdp_prog; } ;
struct TYPE_6__ {TYPE_2__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state; TYPE_1__* profile; TYPE_3__ channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_carrier ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* update_rx ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_priv_channels (struct mlx5e_priv*) ; 
 int mlx5e_open_channels (struct mlx5e_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_queue_update_stats (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xdp_set_closed (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xdp_set_open (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5e_priv*) ; 

int mlx5e_open_locked(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	bool is_xdp = priv->channels.params.xdp_prog;
	int err;

	set_bit(MLX5E_STATE_OPENED, &priv->state);
	if (is_xdp)
		mlx5e_xdp_set_open(priv);

	err = mlx5e_open_channels(priv, &priv->channels);
	if (err)
		goto err_clear_state_opened_flag;

	priv->profile->update_rx(priv);
	mlx5e_activate_priv_channels(priv);
	if (priv->profile->update_carrier)
		priv->profile->update_carrier(priv);

	mlx5e_queue_update_stats(priv);
	return 0;

err_clear_state_opened_flag:
	if (is_xdp)
		mlx5e_xdp_set_closed(priv);
	clear_bit(MLX5E_STATE_OPENED, &priv->state);
	return err;
}