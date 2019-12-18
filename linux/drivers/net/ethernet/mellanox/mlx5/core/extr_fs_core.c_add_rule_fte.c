#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_root_namespace {TYPE_1__* cmds; } ;
struct mlx5_flow_handle {int /*<<< orphan*/  num_rules; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct mlx5_flow_group {TYPE_3__ node; } ;
struct mlx5_flow_destination {int dummy; } ;
struct TYPE_5__ {int active; int /*<<< orphan*/  version; } ;
struct fs_fte {int status; TYPE_2__ node; } ;
struct TYPE_4__ {int (* create_fte ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*,struct fs_fte*) ;int (* update_fte ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*,int,struct fs_fte*) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct mlx5_flow_handle* ERR_PTR (int) ; 
 int FS_FTE_STATUS_EXISTING ; 
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct mlx5_flow_handle* create_flow_handle (struct fs_fte*,struct mlx5_flow_destination*,int,int*,int*) ; 
 int /*<<< orphan*/  destroy_flow_handle (struct fs_fte*,struct mlx5_flow_handle*,struct mlx5_flow_destination*,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_root_namespace* find_root (TYPE_3__*) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_table*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*,struct fs_fte*) ; 
 int stub2 (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*,int,struct fs_fte*) ; 

__attribute__((used)) static struct mlx5_flow_handle *
add_rule_fte(struct fs_fte *fte,
	     struct mlx5_flow_group *fg,
	     struct mlx5_flow_destination *dest,
	     int dest_num,
	     bool update_action)
{
	struct mlx5_flow_root_namespace *root;
	struct mlx5_flow_handle *handle;
	struct mlx5_flow_table *ft;
	int modify_mask = 0;
	int err;
	bool new_rule = false;

	handle = create_flow_handle(fte, dest, dest_num, &modify_mask,
				    &new_rule);
	if (IS_ERR(handle) || !new_rule)
		goto out;

	if (update_action)
		modify_mask |= BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION);

	fs_get_obj(ft, fg->node.parent);
	root = find_root(&fg->node);
	if (!(fte->status & FS_FTE_STATUS_EXISTING))
		err = root->cmds->create_fte(root, ft, fg, fte);
	else
		err = root->cmds->update_fte(root, ft, fg, modify_mask, fte);
	if (err)
		goto free_handle;

	fte->node.active = true;
	fte->status |= FS_FTE_STATUS_EXISTING;
	atomic_inc(&fte->node.version);

out:
	return handle;

free_handle:
	destroy_flow_handle(fte, handle, dest, handle->num_rules);
	return ERR_PTR(err);
}