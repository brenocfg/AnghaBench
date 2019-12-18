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
struct mlx5dr_table {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {struct mlx5dr_table* tbl; } ;
struct mlx5dr_action {TYPE_1__ dest_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_FT ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

struct mlx5dr_action *
mlx5dr_action_create_dest_table(struct mlx5dr_table *tbl)
{
	struct mlx5dr_action *action;

	refcount_inc(&tbl->refcount);

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	if (!action)
		goto dec_ref;

	action->dest_tbl.tbl = tbl;

	return action;

dec_ref:
	refcount_dec(&tbl->refcount);
	return NULL;
}