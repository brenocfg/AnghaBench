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
struct mlx5e_priv {int /*<<< orphan*/  monitor_counters_nb; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_NB_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONITOR_COUNTER ; 
 int /*<<< orphan*/  mlx5_eq_notifier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_monitor_event_handler ; 

__attribute__((used)) static void mlx5e_monitor_counter_start(struct mlx5e_priv *priv)
{
	MLX5_NB_INIT(&priv->monitor_counters_nb, mlx5e_monitor_event_handler,
		     MONITOR_COUNTER);
	mlx5_eq_notifier_register(priv->mdev, &priv->monitor_counters_nb);
}