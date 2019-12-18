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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_l2_rule {int /*<<< orphan*/ * rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_del_l2_flow_rule(struct mlx5e_priv *priv,
				   struct mlx5e_l2_rule *ai)
{
	if (!IS_ERR_OR_NULL(ai->rule)) {
		mlx5_del_flow_rules(ai->rule);
		ai->rule = NULL;
	}
}