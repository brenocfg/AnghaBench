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
struct dm_cache_metadata {int /*<<< orphan*/  flags; } ;
struct dm_block {int dummy; } ;
struct cache_disk_superblock {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  NEEDS_CHECK ; 
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct cache_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int superblock_lock (struct dm_cache_metadata*,struct dm_block**) ; 

int dm_cache_metadata_set_needs_check(struct dm_cache_metadata *cmd)
{
	int r;
	struct dm_block *sblock;
	struct cache_disk_superblock *disk_super;

	WRITE_LOCK(cmd);
	set_bit(NEEDS_CHECK, &cmd->flags);

	r = superblock_lock(cmd, &sblock);
	if (r) {
		DMERR("couldn't read superblock");
		goto out;
	}

	disk_super = dm_block_data(sblock);
	disk_super->flags = cpu_to_le32(cmd->flags);

	dm_bm_unlock(sblock);

out:
	WRITE_UNLOCK(cmd);
	return r;
}