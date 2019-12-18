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
struct mlx5_ib_sq {int /*<<< orphan*/ * flow_rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_flow_rule_vport_sq(struct mlx5_ib_sq *sq)
{
	if (sq->flow_rule)
		mlx5_del_flow_rules(sq->flow_rule);
	sq->flow_rule = NULL;
}