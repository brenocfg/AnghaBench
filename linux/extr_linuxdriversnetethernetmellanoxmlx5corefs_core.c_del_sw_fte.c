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
struct mlx5_flow_steering {int /*<<< orphan*/  ftes_cache; } ;
struct TYPE_2__ {struct fs_node* parent; } ;
struct mlx5_flow_group {scalar_t__ start_index; scalar_t__ index; int /*<<< orphan*/  fte_allocator; int /*<<< orphan*/  hash; int /*<<< orphan*/  ftes_hash; TYPE_1__ node; } ;
struct fs_node {int dummy; } ;
struct fs_fte {scalar_t__ start_index; scalar_t__ index; int /*<<< orphan*/  fte_allocator; int /*<<< orphan*/  hash; int /*<<< orphan*/  ftes_hash; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_group*,struct fs_node*) ; 
 struct mlx5_flow_steering* get_steering (struct fs_node*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  rhash_fte ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_sw_fte(struct fs_node *node)
{
	struct mlx5_flow_steering *steering = get_steering(node);
	struct mlx5_flow_group *fg;
	struct fs_fte *fte;
	int err;

	fs_get_obj(fte, node);
	fs_get_obj(fg, fte->node.parent);

	err = rhashtable_remove_fast(&fg->ftes_hash,
				     &fte->hash,
				     rhash_fte);
	WARN_ON(err);
	ida_simple_remove(&fg->fte_allocator, fte->index - fg->start_index);
	kmem_cache_free(steering->ftes_cache, fte);
}