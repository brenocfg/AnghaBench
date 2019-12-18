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
struct dm_clone_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  sm; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  bitset_root; int /*<<< orphan*/  bitset_info; int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int /*<<< orphan*/  SUPERBLOCK_LOCATION ; 
 int __copy_sm_root (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  __prepare_superblock (struct dm_clone_metadata*,struct superblock_disk*) ; 
 int dm_bitset_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_bitset_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct superblock_disk* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_disk_bitset_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int dm_tm_commit (int /*<<< orphan*/ ,struct dm_block*) ; 
 int dm_tm_create_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 
 int dm_tm_pre_commit (int /*<<< orphan*/ ) ; 
 int superblock_write_lock_zero (struct dm_clone_metadata*,struct dm_block**) ; 

__attribute__((used)) static int __format_metadata(struct dm_clone_metadata *cmd)
{
	int r;
	struct dm_block *sblock;
	struct superblock_disk *sb;

	r = dm_tm_create_with_sm(cmd->bm, SUPERBLOCK_LOCATION, &cmd->tm, &cmd->sm);
	if (r) {
		DMERR("Failed to create transaction manager");
		return r;
	}

	dm_disk_bitset_init(cmd->tm, &cmd->bitset_info);

	r = dm_bitset_empty(&cmd->bitset_info, &cmd->bitset_root);
	if (r) {
		DMERR("Failed to create empty on-disk bitset");
		goto err_with_tm;
	}

	r = dm_bitset_resize(&cmd->bitset_info, cmd->bitset_root, 0,
			     cmd->nr_regions, false, &cmd->bitset_root);
	if (r) {
		DMERR("Failed to resize on-disk bitset to %lu entries", cmd->nr_regions);
		goto err_with_tm;
	}

	/* Flush to disk all blocks, except the superblock */
	r = dm_tm_pre_commit(cmd->tm);
	if (r) {
		DMERR("dm_tm_pre_commit failed");
		goto err_with_tm;
	}

	r = __copy_sm_root(cmd);
	if (r) {
		DMERR("__copy_sm_root failed");
		goto err_with_tm;
	}

	r = superblock_write_lock_zero(cmd, &sblock);
	if (r) {
		DMERR("Failed to write_lock superblock");
		goto err_with_tm;
	}

	sb = dm_block_data(sblock);
	__prepare_superblock(cmd, sb);
	r = dm_tm_commit(cmd->tm, sblock);
	if (r) {
		DMERR("Failed to commit superblock");
		goto err_with_tm;
	}

	return 0;

err_with_tm:
	dm_sm_destroy(cmd->sm);
	dm_tm_destroy(cmd->tm);

	return r;
}