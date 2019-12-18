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
struct TYPE_3__ {struct mlx5_core_dev* mdev; struct mlx5_flow_table* ft; } ;
struct TYPE_4__ {int is_fw_tbl; TYPE_1__ fw_tbl; } ;
struct mlx5dr_action {TYPE_2__ dest_tbl; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_FT ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 

struct mlx5dr_action *
mlx5dr_create_action_dest_flow_fw_table(struct mlx5_flow_table *ft,
					struct mlx5_core_dev *mdev)
{
	struct mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_FT);
	if (!action)
		return NULL;

	action->dest_tbl.is_fw_tbl = 1;
	action->dest_tbl.fw_tbl.ft = ft;
	action->dest_tbl.fw_tbl.mdev = mdev;

	return action;
}