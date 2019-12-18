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
struct TYPE_3__ {int /*<<< orphan*/  num_groups; scalar_t__ active; } ;
struct TYPE_4__ {struct fs_node* parent; } ;
struct mlx5_flow_table {int /*<<< orphan*/  hash; int /*<<< orphan*/  fgs_hash; TYPE_1__ autogroup; int /*<<< orphan*/  fte_allocator; int /*<<< orphan*/  ftes_hash; TYPE_2__ node; } ;
struct mlx5_flow_steering {int /*<<< orphan*/  fgs_cache; } ;
struct mlx5_flow_group {int /*<<< orphan*/  hash; int /*<<< orphan*/  fgs_hash; TYPE_1__ autogroup; int /*<<< orphan*/  fte_allocator; int /*<<< orphan*/  ftes_hash; TYPE_2__ node; } ;
struct fs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_table*,struct fs_node*) ; 
 struct mlx5_flow_steering* get_steering (struct fs_node*) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  rhash_fg ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_sw_flow_group(struct fs_node *node)
{
	struct mlx5_flow_steering *steering = get_steering(node);
	struct mlx5_flow_group *fg;
	struct mlx5_flow_table *ft;
	int err;

	fs_get_obj(fg, node);
	fs_get_obj(ft, fg->node.parent);

	rhashtable_destroy(&fg->ftes_hash);
	ida_destroy(&fg->fte_allocator);
	if (ft->autogroup.active)
		ft->autogroup.num_groups--;
	err = rhltable_remove(&ft->fgs_hash,
			      &fg->hash,
			      rhash_fg);
	WARN_ON(err);
	kmem_cache_free(steering->fgs_cache, fg);
}