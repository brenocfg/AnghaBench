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
struct dm_cache_metadata {int clean_when_opened; int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  tm; scalar_t__ discard_nr_blocks; scalar_t__ discard_block_size; int /*<<< orphan*/  discard_root; int /*<<< orphan*/  discard_info; int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  dirty_info; int /*<<< orphan*/  root; int /*<<< orphan*/  info; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SUPERBLOCK_LOCATION ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  __setup_mapping_info (struct dm_cache_metadata*) ; 
 int __write_initial_superblock (struct dm_cache_metadata*) ; 
 int dm_array_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_bitset_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_disk_bitset_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int dm_tm_create_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 

__attribute__((used)) static int __format_metadata(struct dm_cache_metadata *cmd)
{
	int r;

	r = dm_tm_create_with_sm(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
				 &cmd->tm, &cmd->metadata_sm);
	if (r < 0) {
		DMERR("tm_create_with_sm failed");
		return r;
	}

	__setup_mapping_info(cmd);

	r = dm_array_empty(&cmd->info, &cmd->root);
	if (r < 0)
		goto bad;

	if (separate_dirty_bits(cmd)) {
		dm_disk_bitset_init(cmd->tm, &cmd->dirty_info);
		r = dm_bitset_empty(&cmd->dirty_info, &cmd->dirty_root);
		if (r < 0)
			goto bad;
	}

	dm_disk_bitset_init(cmd->tm, &cmd->discard_info);
	r = dm_bitset_empty(&cmd->discard_info, &cmd->discard_root);
	if (r < 0)
		goto bad;

	cmd->discard_block_size = 0;
	cmd->discard_nr_blocks = 0;

	r = __write_initial_superblock(cmd);
	if (r)
		goto bad;

	cmd->clean_when_opened = true;
	return 0;

bad:
	dm_tm_destroy(cmd->tm);
	dm_sm_destroy(cmd->metadata_sm);

	return r;
}