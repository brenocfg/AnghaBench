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
struct mlx5dr_table {TYPE_1__* dmn; int /*<<< orphan*/  refcount; } ;
struct mlx5dr_matcher {struct mlx5dr_table* tbl; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dr_matcher_remove_from_tbl (struct mlx5dr_matcher*) ; 
 int /*<<< orphan*/  dr_matcher_uninit (struct mlx5dr_matcher*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_matcher*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

int mlx5dr_matcher_destroy(struct mlx5dr_matcher *matcher)
{
	struct mlx5dr_table *tbl = matcher->tbl;

	if (refcount_read(&matcher->refcount) > 1)
		return -EBUSY;

	mutex_lock(&tbl->dmn->mutex);

	dr_matcher_remove_from_tbl(matcher);
	dr_matcher_uninit(matcher);
	refcount_dec(&matcher->tbl->refcount);

	mutex_unlock(&tbl->dmn->mutex);
	kfree(matcher);

	return 0;
}