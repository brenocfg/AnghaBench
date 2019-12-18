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
struct mlx5_hv_vhca_control_block {int control; } ;
struct mlx5_hv_vhca_agent {int /*<<< orphan*/  (* control ) (struct mlx5_hv_vhca_agent*,struct mlx5_hv_vhca_control_block*) ;int /*<<< orphan*/  type; } ;
struct mlx5_hv_vhca {struct mlx5_hv_vhca_agent** agents; } ;

/* Variables and functions */
 int AGENT_MASK (int /*<<< orphan*/ ) ; 
 int MLX5_HV_VHCA_AGENT_MAX ; 
 int /*<<< orphan*/  stub1 (struct mlx5_hv_vhca_agent*,struct mlx5_hv_vhca_control_block*) ; 

__attribute__((used)) static void mlx5_hv_vhca_agents_control(struct mlx5_hv_vhca *hv_vhca,
					struct mlx5_hv_vhca_control_block *block)
{
	int i;

	for (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++) {
		struct mlx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		if (!agent || !agent->control)
			continue;

		if (!(AGENT_MASK(agent->type) & block->control))
			continue;

		agent->control(agent, block);
	}
}