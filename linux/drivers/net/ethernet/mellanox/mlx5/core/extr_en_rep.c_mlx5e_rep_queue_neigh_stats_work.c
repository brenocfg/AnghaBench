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
struct mlx5e_neigh_update_table {int /*<<< orphan*/  min_interval; int /*<<< orphan*/  neigh_stats_work; } ;
struct mlx5e_rep_priv {struct mlx5e_neigh_update_table neigh_update; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5e_rep_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_fc_queue_stats_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5e_rep_queue_neigh_stats_work(struct mlx5e_priv *priv)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;

	mlx5_fc_queue_stats_work(priv->mdev,
				 &neigh_update->neigh_stats_work,
				 neigh_update->min_interval);
}