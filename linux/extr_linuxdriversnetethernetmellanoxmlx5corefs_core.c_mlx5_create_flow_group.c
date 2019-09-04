#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  prev; } ;
struct TYPE_12__ {TYPE_2__ children; } ;
struct TYPE_9__ {scalar_t__ active; } ;
struct mlx5_flow_table {TYPE_4__ node; TYPE_1__ autogroup; } ;
struct mlx5_flow_root_namespace {TYPE_3__* cmds; } ;
struct TYPE_13__ {int active; } ;
struct mlx5_flow_group {TYPE_5__ node; int /*<<< orphan*/  id; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_11__ {int (* create_flow_group ) (struct mlx5_core_dev*,struct mlx5_flow_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EPERM ; 
 struct mlx5_flow_group* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlx5_flow_group*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_group* alloc_insert_flow_group (struct mlx5_flow_table*,void*,void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  down_write_ref_node (TYPE_4__*) ; 
 int /*<<< orphan*/  end_flow_index ; 
 struct mlx5_flow_root_namespace* find_root (TYPE_4__*) ; 
 struct mlx5_core_dev* get_dev (TYPE_4__*) ; 
 void* match_criteria ; 
 void* match_criteria_enable ; 
 int /*<<< orphan*/  start_flow_index ; 
 int stub1 (struct mlx5_core_dev*,struct mlx5_flow_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mlx5_fs_add_fg (struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  tree_put_node (TYPE_5__*) ; 
 int /*<<< orphan*/  up_write_ref_node (TYPE_4__*) ; 

struct mlx5_flow_group *mlx5_create_flow_group(struct mlx5_flow_table *ft,
					       u32 *fg_in)
{
	struct mlx5_flow_root_namespace *root = find_root(&ft->node);
	void *match_criteria = MLX5_ADDR_OF(create_flow_group_in,
					    fg_in, match_criteria);
	u8 match_criteria_enable = MLX5_GET(create_flow_group_in,
					    fg_in,
					    match_criteria_enable);
	int start_index = MLX5_GET(create_flow_group_in, fg_in,
				   start_flow_index);
	int end_index = MLX5_GET(create_flow_group_in, fg_in,
				 end_flow_index);
	struct mlx5_core_dev *dev = get_dev(&ft->node);
	struct mlx5_flow_group *fg;
	int err;

	if (ft->autogroup.active)
		return ERR_PTR(-EPERM);

	down_write_ref_node(&ft->node);
	fg = alloc_insert_flow_group(ft, match_criteria_enable, match_criteria,
				     start_index, end_index,
				     ft->node.children.prev);
	up_write_ref_node(&ft->node);
	if (IS_ERR(fg))
		return fg;

	err = root->cmds->create_flow_group(dev, ft, fg_in, &fg->id);
	if (err) {
		tree_put_node(&fg->node);
		return ERR_PTR(err);
	}
	trace_mlx5_fs_add_fg(fg);
	fg->node.active = true;

	return fg;
}