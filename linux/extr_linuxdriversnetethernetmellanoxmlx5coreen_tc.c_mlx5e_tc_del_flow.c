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
struct mlx5e_tc_flow {int flags; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int MLX5E_TC_FLOW_ESWITCH ; 
 int /*<<< orphan*/  mlx5e_tc_del_fdb_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_del_nic_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 

__attribute__((used)) static void mlx5e_tc_del_flow(struct mlx5e_priv *priv,
			      struct mlx5e_tc_flow *flow)
{
	if (flow->flags & MLX5E_TC_FLOW_ESWITCH)
		mlx5e_tc_del_fdb_flow(priv, flow);
	else
		mlx5e_tc_del_nic_flow(priv, flow);
}