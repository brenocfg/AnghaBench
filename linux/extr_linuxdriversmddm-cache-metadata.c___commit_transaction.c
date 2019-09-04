#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  write_misses; int /*<<< orphan*/  write_hits; int /*<<< orphan*/  read_misses; int /*<<< orphan*/  read_hits; } ;
struct dm_cache_metadata {int /*<<< orphan*/  tm; TYPE_1__ stats; int /*<<< orphan*/  policy_hint_size; int /*<<< orphan*/ * policy_version; int /*<<< orphan*/  policy_name; int /*<<< orphan*/  cache_blocks; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_block_size; int /*<<< orphan*/  discard_root; int /*<<< orphan*/  hint_root; int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  root; int /*<<< orphan*/  flags; int /*<<< orphan*/  discard_info; int /*<<< orphan*/  dirty_info; } ;
struct dm_block {int dummy; } ;
struct cache_disk_superblock {void* write_misses; void* write_hits; void* read_misses; void* read_hits; void* policy_hint_size; void** policy_version; int /*<<< orphan*/  policy_name; void* cache_blocks; void* discard_nr_blocks; void* discard_block_size; void* discard_root; void* hint_root; void* dirty_root; void* mapping_root; void* flags; } ;
typedef  int /*<<< orphan*/  flags_mutator ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  __copy_sm_root (struct dm_cache_metadata*,struct cache_disk_superblock*) ; 
 int __save_sm_root (struct dm_cache_metadata*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dm_bitset_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cache_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_tm_commit (int /*<<< orphan*/ ,struct dm_block*) ; 
 int dm_tm_pre_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_dblock (int /*<<< orphan*/ ) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int superblock_lock (struct dm_cache_metadata*,struct dm_block**) ; 
 int /*<<< orphan*/  update_flags (struct cache_disk_superblock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __commit_transaction(struct dm_cache_metadata *cmd,
				flags_mutator mutator)
{
	int r;
	struct cache_disk_superblock *disk_super;
	struct dm_block *sblock;

	/*
	 * We need to know if the cache_disk_superblock exceeds a 512-byte sector.
	 */
	BUILD_BUG_ON(sizeof(struct cache_disk_superblock) > 512);

	if (separate_dirty_bits(cmd)) {
		r = dm_bitset_flush(&cmd->dirty_info, cmd->dirty_root,
				    &cmd->dirty_root);
		if (r)
			return r;
	}

	r = dm_bitset_flush(&cmd->discard_info, cmd->discard_root,
			    &cmd->discard_root);
	if (r)
		return r;

	r = dm_tm_pre_commit(cmd->tm);
	if (r < 0)
		return r;

	r = __save_sm_root(cmd);
	if (r)
		return r;

	r = superblock_lock(cmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);

	disk_super->flags = cpu_to_le32(cmd->flags);
	if (mutator)
		update_flags(disk_super, mutator);

	disk_super->mapping_root = cpu_to_le64(cmd->root);
	if (separate_dirty_bits(cmd))
		disk_super->dirty_root = cpu_to_le64(cmd->dirty_root);
	disk_super->hint_root = cpu_to_le64(cmd->hint_root);
	disk_super->discard_root = cpu_to_le64(cmd->discard_root);
	disk_super->discard_block_size = cpu_to_le64(cmd->discard_block_size);
	disk_super->discard_nr_blocks = cpu_to_le64(from_dblock(cmd->discard_nr_blocks));
	disk_super->cache_blocks = cpu_to_le32(from_cblock(cmd->cache_blocks));
	strncpy(disk_super->policy_name, cmd->policy_name, sizeof(disk_super->policy_name));
	disk_super->policy_version[0] = cpu_to_le32(cmd->policy_version[0]);
	disk_super->policy_version[1] = cpu_to_le32(cmd->policy_version[1]);
	disk_super->policy_version[2] = cpu_to_le32(cmd->policy_version[2]);
	disk_super->policy_hint_size = cpu_to_le32(cmd->policy_hint_size);

	disk_super->read_hits = cpu_to_le32(cmd->stats.read_hits);
	disk_super->read_misses = cpu_to_le32(cmd->stats.read_misses);
	disk_super->write_hits = cpu_to_le32(cmd->stats.write_hits);
	disk_super->write_misses = cpu_to_le32(cmd->stats.write_misses);
	__copy_sm_root(cmd, disk_super);

	return dm_tm_commit(cmd->tm, sblock);
}