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

/* Variables and functions */
 int /*<<< orphan*/  mlx5_hv_vhca_agent_destroy (struct mlx5_hv_vhca_agent*) ; 

__attribute__((used)) static void mlx5_hv_vhca_control_agent_destroy(struct mlx5_hv_vhca_agent *agent)
{
	mlx5_hv_vhca_agent_destroy(agent);
}