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
struct mlx5_hv_vhca {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_HV_VHCA_AGENT_CONTROL ; 
 struct mlx5_hv_vhca_agent* mlx5_hv_vhca_agent_create (struct mlx5_hv_vhca*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_control_agent_invalidate ; 

__attribute__((used)) static struct mlx5_hv_vhca_agent *
mlx5_hv_vhca_control_agent_create(struct mlx5_hv_vhca *hv_vhca)
{
	return mlx5_hv_vhca_agent_create(hv_vhca, MLX5_HV_VHCA_AGENT_CONTROL,
					 NULL,
					 mlx5_hv_vhca_control_agent_invalidate,
					 NULL, NULL);
}