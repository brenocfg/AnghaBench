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
struct mlx5_flow_table {int /*<<< orphan*/  flags; } ;
struct mlx5_flow_root_namespace {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dr_matcher; } ;
struct mlx5_flow_group {TYPE_1__ fs_dr_matcher; } ;
struct TYPE_4__ {int (* destroy_flow_group ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*) ;} ;

/* Variables and functions */
 scalar_t__ mlx5_dr_is_fw_table (int /*<<< orphan*/ ) ; 
 TYPE_2__* mlx5_fs_cmd_get_fw_cmds () ; 
 int mlx5dr_matcher_destroy (int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*) ; 

__attribute__((used)) static int mlx5_cmd_dr_destroy_flow_group(struct mlx5_flow_root_namespace *ns,
					  struct mlx5_flow_table *ft,
					  struct mlx5_flow_group *fg)
{
	if (mlx5_dr_is_fw_table(ft->flags))
		return mlx5_fs_cmd_get_fw_cmds()->destroy_flow_group(ns, ft, fg);

	return mlx5dr_matcher_destroy(fg->fs_dr_matcher.dr_matcher);
}