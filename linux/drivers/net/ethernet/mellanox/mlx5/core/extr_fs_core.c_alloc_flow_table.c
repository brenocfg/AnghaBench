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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mlx5_flow_table {int level; int op_mod; int type; int max_fte; int /*<<< orphan*/  lock; int /*<<< orphan*/  fwd_rules; int /*<<< orphan*/  flags; int /*<<< orphan*/  vport; TYPE_1__ node; int /*<<< orphan*/  fgs_hash; } ;
typedef  enum fs_flow_table_type { ____Placeholder_fs_flow_table_type } fs_flow_table_type ;
typedef  enum fs_flow_table_op_mod { ____Placeholder_fs_flow_table_op_mod } fs_flow_table_op_mod ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlx5_flow_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  FS_TYPE_FLOW_TABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_table*) ; 
 struct mlx5_flow_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhash_fg ; 
 int rhltable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_table *alloc_flow_table(int level, u16 vport, int max_fte,
						enum fs_flow_table_type table_type,
						enum fs_flow_table_op_mod op_mod,
						u32 flags)
{
	struct mlx5_flow_table *ft;
	int ret;

	ft  = kzalloc(sizeof(*ft), GFP_KERNEL);
	if (!ft)
		return ERR_PTR(-ENOMEM);

	ret = rhltable_init(&ft->fgs_hash, &rhash_fg);
	if (ret) {
		kfree(ft);
		return ERR_PTR(ret);
	}

	ft->level = level;
	ft->node.type = FS_TYPE_FLOW_TABLE;
	ft->op_mod = op_mod;
	ft->type = table_type;
	ft->vport = vport;
	ft->max_fte = max_fte;
	ft->flags = flags;
	INIT_LIST_HEAD(&ft->fwd_rules);
	mutex_init(&ft->lock);

	return ft;
}