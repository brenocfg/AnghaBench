#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_handle {int num_rules; TYPE_1__** rule; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  tree_remove_node (int /*<<< orphan*/ *) ; 

void mlx5_del_flow_rules(struct mlx5_flow_handle *handle)
{
	int i;

	for (i = handle->num_rules - 1; i >= 0; i--)
		tree_remove_node(&handle->rule[i]->node);
	kfree(handle);
}