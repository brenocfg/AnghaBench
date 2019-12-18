#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_rule {int dummy; } ;
struct mlx5dr_matcher {TYPE_2__* tbl; int /*<<< orphan*/  refcount; } ;
struct mlx5dr_match_parameters {int dummy; } ;
struct mlx5dr_action {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dmn; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct mlx5dr_rule* dr_rule_create_rule (struct mlx5dr_matcher*,struct mlx5dr_match_parameters*,size_t,struct mlx5dr_action**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

struct mlx5dr_rule *mlx5dr_rule_create(struct mlx5dr_matcher *matcher,
				       struct mlx5dr_match_parameters *value,
				       size_t num_actions,
				       struct mlx5dr_action *actions[])
{
	struct mlx5dr_rule *rule;

	mutex_lock(&matcher->tbl->dmn->mutex);
	refcount_inc(&matcher->refcount);

	rule = dr_rule_create_rule(matcher, value, num_actions, actions);
	if (!rule)
		refcount_dec(&matcher->refcount);

	mutex_unlock(&matcher->tbl->dmn->mutex);

	return rule;
}