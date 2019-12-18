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
struct mlx5_hv_vhca_agent {struct mlx5_hv_vhca_agent** agents; int /*<<< orphan*/  dev; } ;
struct mlx5_hv_vhca {struct mlx5_hv_vhca** agents; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IS_ERR_OR_NULL (struct mlx5_hv_vhca_agent*) ; 
 size_t MLX5_HV_VHCA_AGENT_CONTROL ; 
 int mlx5_hv_register_invalidate (int /*<<< orphan*/ ,struct mlx5_hv_vhca_agent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_unregister_invalidate (int /*<<< orphan*/ ) ; 
 struct mlx5_hv_vhca_agent* mlx5_hv_vhca_control_agent_create (struct mlx5_hv_vhca_agent*) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_invalidate ; 

int mlx5_hv_vhca_init(struct mlx5_hv_vhca *hv_vhca)
{
	struct mlx5_hv_vhca_agent *agent;
	int err;

	if (IS_ERR_OR_NULL(hv_vhca))
		return IS_ERR_OR_NULL(hv_vhca);

	err = mlx5_hv_register_invalidate(hv_vhca->dev, hv_vhca,
					  mlx5_hv_vhca_invalidate);
	if (err)
		return err;

	agent = mlx5_hv_vhca_control_agent_create(hv_vhca);
	if (IS_ERR_OR_NULL(agent)) {
		mlx5_hv_unregister_invalidate(hv_vhca->dev);
		return IS_ERR_OR_NULL(agent);
	}

	hv_vhca->agents[MLX5_HV_VHCA_AGENT_CONTROL] = agent;

	return 0;
}