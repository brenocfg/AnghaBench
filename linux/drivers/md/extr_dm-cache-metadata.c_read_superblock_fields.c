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
struct TYPE_2__ {void* write_misses; void* write_hits; void* read_misses; void* read_hits; } ;
struct dm_cache_metadata {int changed; void* dirty_root; TYPE_1__ stats; void* policy_hint_size; void** policy_version; int /*<<< orphan*/  policy_name; int /*<<< orphan*/  cache_blocks; void* data_block_size; int /*<<< orphan*/  discard_nr_blocks; void* discard_block_size; void* discard_root; void* hint_root; void* root; void* flags; void* version; } ;
struct cache_disk_superblock {int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  write_misses; int /*<<< orphan*/  write_hits; int /*<<< orphan*/  read_misses; int /*<<< orphan*/  read_hits; int /*<<< orphan*/  policy_hint_size; int /*<<< orphan*/ * policy_version; int /*<<< orphan*/  policy_name; int /*<<< orphan*/  cache_blocks; int /*<<< orphan*/  data_block_size; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_block_size; int /*<<< orphan*/  discard_root; int /*<<< orphan*/  hint_root; int /*<<< orphan*/  mapping_root; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_cblock (void*) ; 
 int /*<<< orphan*/  to_dblock (void*) ; 

__attribute__((used)) static void read_superblock_fields(struct dm_cache_metadata *cmd,
				   struct cache_disk_superblock *disk_super)
{
	cmd->version = le32_to_cpu(disk_super->version);
	cmd->flags = le32_to_cpu(disk_super->flags);
	cmd->root = le64_to_cpu(disk_super->mapping_root);
	cmd->hint_root = le64_to_cpu(disk_super->hint_root);
	cmd->discard_root = le64_to_cpu(disk_super->discard_root);
	cmd->discard_block_size = le64_to_cpu(disk_super->discard_block_size);
	cmd->discard_nr_blocks = to_dblock(le64_to_cpu(disk_super->discard_nr_blocks));
	cmd->data_block_size = le32_to_cpu(disk_super->data_block_size);
	cmd->cache_blocks = to_cblock(le32_to_cpu(disk_super->cache_blocks));
	strncpy(cmd->policy_name, disk_super->policy_name, sizeof(cmd->policy_name));
	cmd->policy_version[0] = le32_to_cpu(disk_super->policy_version[0]);
	cmd->policy_version[1] = le32_to_cpu(disk_super->policy_version[1]);
	cmd->policy_version[2] = le32_to_cpu(disk_super->policy_version[2]);
	cmd->policy_hint_size = le32_to_cpu(disk_super->policy_hint_size);

	cmd->stats.read_hits = le32_to_cpu(disk_super->read_hits);
	cmd->stats.read_misses = le32_to_cpu(disk_super->read_misses);
	cmd->stats.write_hits = le32_to_cpu(disk_super->write_hits);
	cmd->stats.write_misses = le32_to_cpu(disk_super->write_misses);

	if (separate_dirty_bits(cmd))
		cmd->dirty_root = le64_to_cpu(disk_super->dirty_root);

	cmd->changed = false;
}