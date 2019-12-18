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
struct dm_cache_metadata {int changed; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_block_size; int /*<<< orphan*/  discard_root; int /*<<< orphan*/  discard_info; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int dm_bitset_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_dblock (int /*<<< orphan*/ ) ; 

int dm_cache_discard_bitset_resize(struct dm_cache_metadata *cmd,
				   sector_t discard_block_size,
				   dm_dblock_t new_nr_entries)
{
	int r;

	WRITE_LOCK(cmd);
	r = dm_bitset_resize(&cmd->discard_info,
			     cmd->discard_root,
			     from_dblock(cmd->discard_nr_blocks),
			     from_dblock(new_nr_entries),
			     false, &cmd->discard_root);
	if (!r) {
		cmd->discard_block_size = discard_block_size;
		cmd->discard_nr_blocks = new_nr_entries;
	}

	cmd->changed = true;
	WRITE_UNLOCK(cmd);

	return r;
}