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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5dr_table {int /*<<< orphan*/  refcount; TYPE_1__* dmn; } ;
struct mlx5dr_matcher {int /*<<< orphan*/  matcher_list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  prio; struct mlx5dr_table* tbl; } ;
struct mlx5dr_match_parameters {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dr_matcher_add_to_tbl (struct mlx5dr_matcher*) ; 
 int dr_matcher_init (struct mlx5dr_matcher*,struct mlx5dr_match_parameters*) ; 
 int /*<<< orphan*/  dr_matcher_uninit (struct mlx5dr_matcher*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_matcher*) ; 
 struct mlx5dr_matcher* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct mlx5dr_matcher *
mlx5dr_matcher_create(struct mlx5dr_table *tbl,
		      u16 priority,
		      u8 match_criteria_enable,
		      struct mlx5dr_match_parameters *mask)
{
	struct mlx5dr_matcher *matcher;
	int ret;

	refcount_inc(&tbl->refcount);

	matcher = kzalloc(sizeof(*matcher), GFP_KERNEL);
	if (!matcher)
		goto dec_ref;

	matcher->tbl = tbl;
	matcher->prio = priority;
	matcher->match_criteria = match_criteria_enable;
	refcount_set(&matcher->refcount, 1);
	INIT_LIST_HEAD(&matcher->matcher_list);

	mutex_lock(&tbl->dmn->mutex);

	ret = dr_matcher_init(matcher, mask);
	if (ret)
		goto free_matcher;

	ret = dr_matcher_add_to_tbl(matcher);
	if (ret)
		goto matcher_uninit;

	mutex_unlock(&tbl->dmn->mutex);

	return matcher;

matcher_uninit:
	dr_matcher_uninit(matcher);
free_matcher:
	mutex_unlock(&tbl->dmn->mutex);
	kfree(matcher);
dec_ref:
	refcount_dec(&tbl->refcount);
	return NULL;
}