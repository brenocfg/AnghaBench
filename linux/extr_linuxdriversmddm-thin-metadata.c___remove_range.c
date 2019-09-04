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
struct dm_thin_device {unsigned int mapped_blocks; int changed; int /*<<< orphan*/  id; struct dm_pool_metadata* pmd; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root; int /*<<< orphan*/  tl_info; int /*<<< orphan*/  bl_info; int /*<<< orphan*/  tm; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_lookup_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_remove_leaves (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __remove_range(struct dm_thin_device *td, dm_block_t begin, dm_block_t end)
{
	int r;
	unsigned count, total_count = 0;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[1] = { td->id };
	__le64 value;
	dm_block_t mapping_root;

	/*
	 * Find the mapping tree
	 */
	r = dm_btree_lookup(&pmd->tl_info, pmd->root, keys, &value);
	if (r)
		return r;

	/*
	 * Remove from the mapping tree, taking care to inc the
	 * ref count so it doesn't get deleted.
	 */
	mapping_root = le64_to_cpu(value);
	dm_tm_inc(pmd->tm, mapping_root);
	r = dm_btree_remove(&pmd->tl_info, pmd->root, keys, &pmd->root);
	if (r)
		return r;

	/*
	 * Remove leaves stops at the first unmapped entry, so we have to
	 * loop round finding mapped ranges.
	 */
	while (begin < end) {
		r = dm_btree_lookup_next(&pmd->bl_info, mapping_root, &begin, &begin, &value);
		if (r == -ENODATA)
			break;

		if (r)
			return r;

		if (begin >= end)
			break;

		r = dm_btree_remove_leaves(&pmd->bl_info, mapping_root, &begin, end, &mapping_root, &count);
		if (r)
			return r;

		total_count += count;
	}

	td->mapped_blocks -= total_count;
	td->changed = 1;

	/*
	 * Reinsert the mapping tree.
	 */
	value = cpu_to_le64(mapping_root);
	__dm_bless_for_disk(&value);
	return dm_btree_insert(&pmd->tl_info, pmd->root, keys, &value, &pmd->root);
}