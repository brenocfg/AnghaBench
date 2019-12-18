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
struct dm_cache_metadata {int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;
struct cache_disk_superblock {int dummy; } ;
typedef  int /*<<< orphan*/  flags_mutator ;

/* Variables and functions */
 struct cache_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_bm_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  read_superblock_fields (struct dm_cache_metadata*,struct cache_disk_superblock*) ; 
 int superblock_lock (struct dm_cache_metadata*,struct dm_block**) ; 
 int /*<<< orphan*/  update_flags (struct cache_disk_superblock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __begin_transaction_flags(struct dm_cache_metadata *cmd,
				     flags_mutator mutator)
{
	int r;
	struct cache_disk_superblock *disk_super;
	struct dm_block *sblock;

	r = superblock_lock(cmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	update_flags(disk_super, mutator);
	read_superblock_fields(cmd, disk_super);
	dm_bm_unlock(sblock);

	return dm_bm_flush(cmd->bm);
}