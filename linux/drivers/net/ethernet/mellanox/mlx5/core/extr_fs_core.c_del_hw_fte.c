#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct fs_node* parent; } ;
struct mlx5_flow_table {int /*<<< orphan*/  id; int /*<<< orphan*/  index; TYPE_2__ node; } ;
struct mlx5_flow_root_namespace {TYPE_1__* cmds; } ;
struct mlx5_flow_group {int /*<<< orphan*/  id; int /*<<< orphan*/  index; TYPE_2__ node; } ;
struct mlx5_core_dev {int dummy; } ;
struct fs_node {scalar_t__ active; } ;
struct fs_fte {int /*<<< orphan*/  id; int /*<<< orphan*/  index; TYPE_2__ node; } ;
struct TYPE_4__ {int (* delete_fte ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_table*) ;} ;

/* Variables and functions */
 struct mlx5_flow_root_namespace* find_root (TYPE_2__*) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_table*,struct fs_node*) ; 
 struct mlx5_core_dev* get_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  trace_mlx5_fs_del_fte (struct mlx5_flow_table*) ; 

__attribute__((used)) static void del_hw_fte(struct fs_node *node)
{
	struct mlx5_flow_root_namespace *root;
	struct mlx5_flow_table *ft;
	struct mlx5_flow_group *fg;
	struct mlx5_core_dev *dev;
	struct fs_fte *fte;
	int err;

	fs_get_obj(fte, node);
	fs_get_obj(fg, fte->node.parent);
	fs_get_obj(ft, fg->node.parent);

	trace_mlx5_fs_del_fte(fte);
	dev = get_dev(&ft->node);
	root = find_root(&ft->node);
	if (node->active) {
		err = root->cmds->delete_fte(root, ft, fte);
		if (err)
			mlx5_core_warn(dev,
				       "flow steering can't delete fte in index %d of flow group id %d\n",
				       fte->index, fg->id);
		node->active = 0;
	}
}