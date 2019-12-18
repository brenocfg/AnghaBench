#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  active; } ;
struct mlx5_flow_group {TYPE_1__ node; int /*<<< orphan*/  ftes_hash; } ;
struct fs_fte {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_LOCK_CHILD ; 
 int /*<<< orphan*/  FS_LOCK_PARENT ; 
 int /*<<< orphan*/  nested_down_read_ref_node (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_down_write_ref_node (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhash_fte ; 
 struct fs_fte* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_get_node (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_put_node (TYPE_1__*,int) ; 
 int /*<<< orphan*/  up_read_ref_node (TYPE_1__*) ; 
 int /*<<< orphan*/  up_write_ref_node (TYPE_1__*,int) ; 

__attribute__((used)) static struct fs_fte *
lookup_fte_locked(struct mlx5_flow_group *g,
		  const u32 *match_value,
		  bool take_write)
{
	struct fs_fte *fte_tmp;

	if (take_write)
		nested_down_write_ref_node(&g->node, FS_LOCK_PARENT);
	else
		nested_down_read_ref_node(&g->node, FS_LOCK_PARENT);
	fte_tmp = rhashtable_lookup_fast(&g->ftes_hash, match_value,
					 rhash_fte);
	if (!fte_tmp || !tree_get_node(&fte_tmp->node)) {
		fte_tmp = NULL;
		goto out;
	}
	if (!fte_tmp->node.active) {
		tree_put_node(&fte_tmp->node, false);
		fte_tmp = NULL;
		goto out;
	}

	nested_down_write_ref_node(&fte_tmp->node, FS_LOCK_CHILD);
out:
	if (take_write)
		up_write_ref_node(&g->node, false);
	else
		up_read_ref_node(&g->node);
	return fte_tmp;
}