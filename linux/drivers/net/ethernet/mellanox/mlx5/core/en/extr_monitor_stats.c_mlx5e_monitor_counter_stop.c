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
struct mlx5e_priv {int /*<<< orphan*/  monitor_counters_work; int /*<<< orphan*/  monitor_counters_nb; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_monitor_counter_stop(struct mlx5e_priv *priv)
{
	mlx5_eq_notifier_unregister(priv->mdev, &priv->monitor_counters_nb);
	cancel_work_sync(&priv->monitor_counters_work);
}