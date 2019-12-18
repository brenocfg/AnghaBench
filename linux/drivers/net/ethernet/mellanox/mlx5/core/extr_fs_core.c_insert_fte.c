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
struct TYPE_4__ {int /*<<< orphan*/  children; } ;
struct mlx5_flow_group {int start_index; int /*<<< orphan*/  fte_allocator; TYPE_2__ node; int /*<<< orphan*/  ftes_hash; int /*<<< orphan*/  max_ftes; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct fs_fte {int index; TYPE_1__ node; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhash_fte ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_add_node (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int insert_fte(struct mlx5_flow_group *fg, struct fs_fte *fte)
{
	int index;
	int ret;

	index = ida_simple_get(&fg->fte_allocator, 0, fg->max_ftes, GFP_KERNEL);
	if (index < 0)
		return index;

	fte->index = index + fg->start_index;
	ret = rhashtable_insert_fast(&fg->ftes_hash,
				     &fte->hash,
				     rhash_fte);
	if (ret)
		goto err_ida_remove;

	tree_add_node(&fte->node, &fg->node);
	list_add_tail(&fte->node.list, &fg->node.children);
	return 0;

err_ida_remove:
	ida_simple_remove(&fg->fte_allocator, index);
	return ret;
}