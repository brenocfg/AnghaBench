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
struct mlx5e_tc_flow {struct mlx5e_priv* priv; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_del_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 

__attribute__((used)) static void _mlx5e_tc_del_flow(void *ptr, void *arg)
{
	struct mlx5e_tc_flow *flow = ptr;
	struct mlx5e_priv *priv = flow->priv;

	mlx5e_tc_del_flow(priv, flow);
	kfree(flow);
}