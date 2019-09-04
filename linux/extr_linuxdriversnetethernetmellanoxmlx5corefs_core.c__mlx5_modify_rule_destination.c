#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {int action; } ;
struct mlx5_flow_table {TYPE_4__ node; int /*<<< orphan*/  id; TYPE_2__ action; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct mlx5_flow_rule {int /*<<< orphan*/  dest_attr; TYPE_1__ node; } ;
struct mlx5_flow_root_namespace {TYPE_3__* cmds; } ;
struct mlx5_flow_group {TYPE_4__ node; int /*<<< orphan*/  id; TYPE_2__ action; } ;
struct mlx5_flow_destination {int dummy; } ;
struct fs_fte {TYPE_4__ node; int /*<<< orphan*/  id; TYPE_2__ action; } ;
struct TYPE_10__ {int (* update_fte ) (int /*<<< orphan*/ ,struct mlx5_flow_table*,int /*<<< orphan*/ ,int,struct mlx5_flow_table*) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int /*<<< orphan*/  MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST ; 
 int /*<<< orphan*/  down_write_ref_node (TYPE_4__*) ; 
 struct mlx5_flow_root_namespace* find_root (TYPE_4__*) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dev (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5_flow_destination*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct mlx5_flow_table*,int /*<<< orphan*/ ,int,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  up_write_ref_node (TYPE_4__*) ; 

__attribute__((used)) static int _mlx5_modify_rule_destination(struct mlx5_flow_rule *rule,
					 struct mlx5_flow_destination *dest)
{
	struct mlx5_flow_root_namespace *root;
	struct mlx5_flow_table *ft;
	struct mlx5_flow_group *fg;
	struct fs_fte *fte;
	int modify_mask = BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST);
	int err = 0;

	fs_get_obj(fte, rule->node.parent);
	if (!(fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		return -EINVAL;
	down_write_ref_node(&fte->node);
	fs_get_obj(fg, fte->node.parent);
	fs_get_obj(ft, fg->node.parent);

	memcpy(&rule->dest_attr, dest, sizeof(*dest));
	root = find_root(&ft->node);
	err = root->cmds->update_fte(get_dev(&ft->node), ft, fg->id,
				     modify_mask, fte);
	up_write_ref_node(&fte->node);

	return err;
}