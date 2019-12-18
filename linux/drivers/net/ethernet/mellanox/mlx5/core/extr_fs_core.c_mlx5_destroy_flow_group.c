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
struct mlx5_flow_group {int /*<<< orphan*/  id; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_remove_node (int /*<<< orphan*/ *,int) ; 

void mlx5_destroy_flow_group(struct mlx5_flow_group *fg)
{
	if (tree_remove_node(&fg->node, false))
		mlx5_core_warn(get_dev(&fg->node), "Flow group %d wasn't destroyed, refcount > 1\n",
			       fg->id);
}