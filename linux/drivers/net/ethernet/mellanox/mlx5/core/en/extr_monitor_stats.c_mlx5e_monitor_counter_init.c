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
struct mlx5e_priv {int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  monitor_counters_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_monitor_counter_arm (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_monitor_counter_start (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_monitor_counters_work ; 
 int /*<<< orphan*/  mlx5e_set_monitor_counter (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5e_monitor_counter_init(struct mlx5e_priv *priv)
{
	INIT_WORK(&priv->monitor_counters_work, mlx5e_monitor_counters_work);
	mlx5e_monitor_counter_start(priv);
	mlx5e_set_monitor_counter(priv);
	mlx5e_monitor_counter_arm(priv);
	queue_work(priv->wq, &priv->update_stats_work);
}