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
struct mlx5_hv_vhca_agent {size_t type; int /*<<< orphan*/  (* cleanup ) (struct mlx5_hv_vhca_agent*) ;struct mlx5_hv_vhca* hv_vhca; } ;
struct mlx5_hv_vhca {int /*<<< orphan*/  agents_lock; struct mlx5_hv_vhca_agent** agents; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_agents_update (struct mlx5_hv_vhca*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_hv_vhca_agent*) ; 

void mlx5_hv_vhca_agent_destroy(struct mlx5_hv_vhca_agent *agent)
{
	struct mlx5_hv_vhca *hv_vhca = agent->hv_vhca;

	mutex_lock(&hv_vhca->agents_lock);

	if (WARN_ON(agent != hv_vhca->agents[agent->type])) {
		mutex_unlock(&hv_vhca->agents_lock);
		return;
	}

	hv_vhca->agents[agent->type] = NULL;
	mutex_unlock(&hv_vhca->agents_lock);

	if (agent->cleanup)
		agent->cleanup(agent);

	kfree(agent);

	mlx5_hv_vhca_agents_update(hv_vhca);
}