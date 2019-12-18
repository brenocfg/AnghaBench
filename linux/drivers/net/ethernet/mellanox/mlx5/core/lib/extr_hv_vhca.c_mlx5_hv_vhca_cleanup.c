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
struct mlx5_hv_vhca_agent {int dummy; } ;
struct mlx5_hv_vhca {int /*<<< orphan*/  dev; int /*<<< orphan*/  agents_lock; struct mlx5_hv_vhca_agent** agents; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_hv_vhca*) ; 
 size_t MLX5_HV_VHCA_AGENT_CONTROL ; 
 int MLX5_HV_VHCA_AGENT_MAX ; 
 int /*<<< orphan*/  WARN_ON (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  mlx5_hv_unregister_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_control_agent_destroy (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_hv_vhca_cleanup(struct mlx5_hv_vhca *hv_vhca)
{
	struct mlx5_hv_vhca_agent *agent;
	int i;

	if (IS_ERR_OR_NULL(hv_vhca))
		return;

	agent = hv_vhca->agents[MLX5_HV_VHCA_AGENT_CONTROL];
	if (agent)
		mlx5_hv_vhca_control_agent_destroy(agent);

	mutex_lock(&hv_vhca->agents_lock);
	for (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++)
		WARN_ON(hv_vhca->agents[i]);

	mutex_unlock(&hv_vhca->agents_lock);

	mlx5_hv_unregister_invalidate(hv_vhca->dev);
}