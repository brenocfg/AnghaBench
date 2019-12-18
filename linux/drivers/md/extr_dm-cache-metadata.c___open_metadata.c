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
struct dm_cache_metadata {unsigned long data_block_size; int /*<<< orphan*/  clean_when_opened; int /*<<< orphan*/  discard_info; int /*<<< orphan*/  tm; int /*<<< orphan*/  dirty_info; int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;
struct cache_disk_superblock {int /*<<< orphan*/  flags; int /*<<< orphan*/  metadata_space_map_root; int /*<<< orphan*/  data_block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SUPERBLOCK_LOCATION ; 
 int /*<<< orphan*/  CLEAN_SHUTDOWN ; 
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int EINVAL ; 
 int __check_incompat_features (struct cache_disk_superblock*,struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  __setup_mapping_info (struct dm_cache_metadata*) ; 
 struct cache_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  dm_disk_bitset_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dm_tm_open_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int superblock_read_lock (struct dm_cache_metadata*,struct dm_block**) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int __open_metadata(struct dm_cache_metadata *cmd)
{
	int r;
	struct dm_block *sblock;
	struct cache_disk_superblock *disk_super;
	unsigned long sb_flags;

	r = superblock_read_lock(cmd, &sblock);
	if (r < 0) {
		DMERR("couldn't read lock superblock");
		return r;
	}

	disk_super = dm_block_data(sblock);

	/* Verify the data block size hasn't changed */
	if (le32_to_cpu(disk_super->data_block_size) != cmd->data_block_size) {
		DMERR("changing the data block size (from %u to %llu) is not supported",
		      le32_to_cpu(disk_super->data_block_size),
		      (unsigned long long)cmd->data_block_size);
		r = -EINVAL;
		goto bad;
	}

	r = __check_incompat_features(disk_super, cmd);
	if (r < 0)
		goto bad;

	r = dm_tm_open_with_sm(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
			       disk_super->metadata_space_map_root,
			       sizeof(disk_super->metadata_space_map_root),
			       &cmd->tm, &cmd->metadata_sm);
	if (r < 0) {
		DMERR("tm_open_with_sm failed");
		goto bad;
	}

	__setup_mapping_info(cmd);
	dm_disk_bitset_init(cmd->tm, &cmd->dirty_info);
	dm_disk_bitset_init(cmd->tm, &cmd->discard_info);
	sb_flags = le32_to_cpu(disk_super->flags);
	cmd->clean_when_opened = test_bit(CLEAN_SHUTDOWN, &sb_flags);
	dm_bm_unlock(sblock);

	return 0;

bad:
	dm_bm_unlock(sblock);
	return r;
}