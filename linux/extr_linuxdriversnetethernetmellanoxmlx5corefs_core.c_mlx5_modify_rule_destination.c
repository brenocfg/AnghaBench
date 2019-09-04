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
struct mlx5_flow_destination {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest_attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int _mlx5_modify_rule_destination (TYPE_1__*,struct mlx5_flow_destination*) ; 
 scalar_t__ mlx5_flow_dests_cmp (struct mlx5_flow_destination*,int /*<<< orphan*/ *) ; 

int mlx5_modify_rule_destination(struct mlx5_flow_handle *handle,
				 struct mlx5_flow_destination *new_dest,
				 struct mlx5_flow_destination *old_dest)
{
	int i;

	if (!old_dest) {
		if (handle->num_rules != 1)
			return -EINVAL;
		return _mlx5_modify_rule_destination(handle->rule[0],
						     new_dest);
	}

	for (i = 0; i < handle->num_rules; i++) {
		if (mlx5_flow_dests_cmp(new_dest, &handle->rule[i]->dest_attr))
			return _mlx5_modify_rule_destination(handle->rule[i],
							     new_dest);
	}

	return -EINVAL;
}