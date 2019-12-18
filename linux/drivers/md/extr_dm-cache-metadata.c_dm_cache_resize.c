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
struct dm_cache_metadata {int changed; int /*<<< orphan*/  cache_blocks; int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  dirty_info; int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dm_unbless_for_disk (int /*<<< orphan*/ *) ; 
 int blocks_are_unmapped_or_clean (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int dm_array_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_bitset_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 

int dm_cache_resize(struct dm_cache_metadata *cmd, dm_cblock_t new_cache_size)
{
	int r;
	bool clean;
	__le64 null_mapping = pack_value(0, 0);

	WRITE_LOCK(cmd);
	__dm_bless_for_disk(&null_mapping);

	if (from_cblock(new_cache_size) < from_cblock(cmd->cache_blocks)) {
		r = blocks_are_unmapped_or_clean(cmd, new_cache_size, cmd->cache_blocks, &clean);
		if (r) {
			__dm_unbless_for_disk(&null_mapping);
			goto out;
		}

		if (!clean) {
			DMERR("unable to shrink cache due to dirty blocks");
			r = -EINVAL;
			__dm_unbless_for_disk(&null_mapping);
			goto out;
		}
	}

	r = dm_array_resize(&cmd->info, cmd->root, from_cblock(cmd->cache_blocks),
			    from_cblock(new_cache_size),
			    &null_mapping, &cmd->root);
	if (r)
		goto out;

	if (separate_dirty_bits(cmd)) {
		r = dm_bitset_resize(&cmd->dirty_info, cmd->dirty_root,
				     from_cblock(cmd->cache_blocks), from_cblock(new_cache_size),
				     false, &cmd->dirty_root);
		if (r)
			goto out;
	}

	cmd->cache_blocks = new_cache_size;
	cmd->changed = true;

out:
	WRITE_UNLOCK(cmd);

	return r;
}