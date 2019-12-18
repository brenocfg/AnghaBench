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
struct mlx5dr_table {int dummy; } ;
struct mlx5dr_action {int dummy; } ;
struct TYPE_2__ {struct mlx5dr_action* miss_action; struct mlx5dr_table* dr_table; } ;
struct mlx5_flow_table {TYPE_1__ fs_dr_table; } ;
struct mlx5_flow_root_namespace {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx5_core_err (int /*<<< orphan*/ ,char*,int) ; 
 struct mlx5dr_action* mlx5dr_action_create_dest_table (struct mlx5dr_table*) ; 
 int mlx5dr_action_destroy (struct mlx5dr_action*) ; 
 int mlx5dr_table_set_miss_action (struct mlx5dr_table*,struct mlx5dr_action*) ; 

__attribute__((used)) static int set_miss_action(struct mlx5_flow_root_namespace *ns,
			   struct mlx5_flow_table *ft,
			   struct mlx5_flow_table *next_ft)
{
	struct mlx5dr_action *old_miss_action;
	struct mlx5dr_action *action = NULL;
	struct mlx5dr_table *next_tbl;
	int err;

	next_tbl = next_ft ? next_ft->fs_dr_table.dr_table : NULL;
	if (next_tbl) {
		action = mlx5dr_action_create_dest_table(next_tbl);
		if (!action)
			return -EINVAL;
	}
	old_miss_action = ft->fs_dr_table.miss_action;
	err = mlx5dr_table_set_miss_action(ft->fs_dr_table.dr_table, action);
	if (err && action) {
		err = mlx5dr_action_destroy(action);
		if (err) {
			action = NULL;
			mlx5_core_err(ns->dev, "Failed to destroy action (%d)\n",
				      err);
		}
	}
	ft->fs_dr_table.miss_action = action;
	if (old_miss_action) {
		err = mlx5dr_action_destroy(old_miss_action);
		if (err)
			mlx5_core_err(ns->dev, "Failed to destroy action (%d)\n",
				      err);
	}

	return err;
}