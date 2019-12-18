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
struct superblock_disk {int dummy; } ;
struct dm_clone_metadata {int hydration_done; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  region_map; int /*<<< orphan*/  tm; int /*<<< orphan*/  bitset_root; int /*<<< orphan*/  bitset_info; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int __copy_sm_root (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  __prepare_superblock (struct dm_clone_metadata*,struct superblock_disk*) ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_bitset_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct superblock_disk* dm_block_data (struct dm_block*) ; 
 int dm_tm_commit (int /*<<< orphan*/ ,struct dm_block*) ; 
 int dm_tm_pre_commit (int /*<<< orphan*/ ) ; 
 int superblock_write_lock_zero (struct dm_clone_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __metadata_commit(struct dm_clone_metadata *cmd)
{
	int r;
	struct dm_block *sblock;
	struct superblock_disk *sb;

	/* Flush bitset cache */
	r = dm_bitset_flush(&cmd->bitset_info, cmd->bitset_root, &cmd->bitset_root);
	if (r) {
		DMERR("dm_bitset_flush failed");
		return r;
	}

	/* Flush to disk all blocks, except the superblock */
	r = dm_tm_pre_commit(cmd->tm);
	if (r) {
		DMERR("dm_tm_pre_commit failed");
		return r;
	}

	/* Save the space map root in cmd->metadata_space_map_root */
	r = __copy_sm_root(cmd);
	if (r) {
		DMERR("__copy_sm_root failed");
		return r;
	}

	/* Lock the superblock */
	r = superblock_write_lock_zero(cmd, &sblock);
	if (r) {
		DMERR("Failed to write_lock superblock");
		return r;
	}

	/* Save the metadata in superblock */
	sb = dm_block_data(sblock);
	__prepare_superblock(cmd, sb);

	/* Unlock superblock and commit it to disk */
	r = dm_tm_commit(cmd->tm, sblock);
	if (r) {
		DMERR("Failed to commit superblock");
		return r;
	}

	/*
	 * FIXME: Find a more efficient way to check if the hydration is done.
	 */
	if (bitmap_full(cmd->region_map, cmd->nr_regions))
		cmd->hydration_done = true;

	return 0;
}