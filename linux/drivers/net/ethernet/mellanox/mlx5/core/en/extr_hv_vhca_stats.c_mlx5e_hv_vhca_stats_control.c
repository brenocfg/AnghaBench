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
struct mlx5e_hv_vhca_stats_agent {int /*<<< orphan*/  delay; int /*<<< orphan*/  work; } ;
struct mlx5e_priv {int /*<<< orphan*/  wq; struct mlx5e_hv_vhca_stats_agent stats_agent; int /*<<< orphan*/  max_nch; } ;
struct mlx5_hv_vhca_control_block {int command; int /*<<< orphan*/  rings; int /*<<< orphan*/  version; } ;
struct mlx5_hv_vhca_agent {int dummy; } ;

/* Variables and functions */
 int MLX5_HV_VHCA_STATS_UPDATE_ONCE ; 
 int /*<<< orphan*/  MLX5_HV_VHCA_STATS_VERSION ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* mlx5_hv_vhca_agent_priv (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_hv_vhca_stats_control(struct mlx5_hv_vhca_agent *agent,
					struct mlx5_hv_vhca_control_block *block)
{
	struct mlx5e_hv_vhca_stats_agent *sagent;
	struct mlx5e_priv *priv;

	priv = mlx5_hv_vhca_agent_priv(agent);
	sagent = &priv->stats_agent;

	block->version = MLX5_HV_VHCA_STATS_VERSION;
	block->rings   = priv->max_nch;

	if (!block->command) {
		cancel_delayed_work_sync(&priv->stats_agent.work);
		return;
	}

	sagent->delay = block->command == MLX5_HV_VHCA_STATS_UPDATE_ONCE ? 0 :
			msecs_to_jiffies(block->command * 100);

	queue_delayed_work(priv->wq, &sagent->work, sagent->delay);
}