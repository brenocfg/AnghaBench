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
struct mlx5e_profile {int /*<<< orphan*/  (* cleanup_tx ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* cleanup_rx ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* disable ) (struct mlx5e_priv*) ;} ;
struct mlx5e_priv {int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  drop_rq; int /*<<< orphan*/  wq; int /*<<< orphan*/  state; struct mlx5e_profile* profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_DESTROYING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_drop_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_q_counters (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  stub3 (struct mlx5e_priv*) ; 

void mlx5e_detach_netdev(struct mlx5e_priv *priv)
{
	const struct mlx5e_profile *profile = priv->profile;

	set_bit(MLX5E_STATE_DESTROYING, &priv->state);

	if (profile->disable)
		profile->disable(priv);
	flush_workqueue(priv->wq);

	profile->cleanup_rx(priv);
	mlx5e_close_drop_rq(&priv->drop_rq);
	mlx5e_destroy_q_counters(priv);
	profile->cleanup_tx(priv);
	cancel_delayed_work_sync(&priv->update_stats_work);
}