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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct mlx5e_priv {TYPE_1__ stats_agent; } ;
struct mlx5_hv_vhca_agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* mlx5_hv_vhca_agent_priv (struct mlx5_hv_vhca_agent*) ; 

__attribute__((used)) static void mlx5e_hv_vhca_stats_cleanup(struct mlx5_hv_vhca_agent *agent)
{
	struct mlx5e_priv *priv = mlx5_hv_vhca_agent_priv(agent);

	cancel_delayed_work_sync(&priv->stats_agent.work);
}