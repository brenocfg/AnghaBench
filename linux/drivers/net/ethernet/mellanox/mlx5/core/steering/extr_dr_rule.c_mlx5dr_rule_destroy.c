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
struct mlx5dr_table {TYPE_1__* dmn; } ;
struct mlx5dr_rule {struct mlx5dr_matcher* matcher; } ;
struct mlx5dr_matcher {int /*<<< orphan*/  refcount; struct mlx5dr_table* tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int dr_rule_destroy_rule (struct mlx5dr_rule*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 

int mlx5dr_rule_destroy(struct mlx5dr_rule *rule)
{
	struct mlx5dr_matcher *matcher = rule->matcher;
	struct mlx5dr_table *tbl = rule->matcher->tbl;
	int ret;

	mutex_lock(&tbl->dmn->mutex);

	ret = dr_rule_destroy_rule(rule);

	mutex_unlock(&tbl->dmn->mutex);

	if (!ret)
		refcount_dec(&matcher->refcount);
	return ret;
}