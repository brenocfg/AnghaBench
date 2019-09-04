#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_group {int /*<<< orphan*/  node; int /*<<< orphan*/  ftes_hash; } ;
struct fs_fte {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_LOCK_CHILD ; 
 int /*<<< orphan*/  FS_LOCK_PARENT ; 
 int /*<<< orphan*/  nested_down_read_ref_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_down_write_ref_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhash_fte ; 
 struct fs_fte* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read_ref_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write_ref_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fs_fte *
lookup_fte_locked(struct mlx5_flow_group *g,
		  u32 *match_value,
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

	nested_down_write_ref_node(&fte_tmp->node, FS_LOCK_CHILD);
out:
	if (take_write)
		up_write_ref_node(&g->node);
	else
		up_read_ref_node(&g->node);
	return fte_tmp;
}