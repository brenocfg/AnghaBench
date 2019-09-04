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
struct superblock_disk {int /*<<< orphan*/  metadata_snap; int /*<<< orphan*/  era_array_root; int /*<<< orphan*/  writeset_tree_root; int /*<<< orphan*/  current_era; int /*<<< orphan*/  nr_blocks; int /*<<< orphan*/  data_block_size; int /*<<< orphan*/  metadata_space_map_root; } ;
struct era_metadata {int archived_writesets; void* metadata_snap; void* era_array_root; void* writeset_tree_root; void* current_era; void* nr_blocks; void* block_size; int /*<<< orphan*/  sm; int /*<<< orphan*/  tm; int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  SUPERBLOCK_LOCATION ; 
 struct superblock_disk* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int dm_tm_open_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_infos (struct era_metadata*) ; 
 int superblock_read_lock (struct era_metadata*,struct dm_block**) ; 

__attribute__((used)) static int open_metadata(struct era_metadata *md)
{
	int r;
	struct dm_block *sblock;
	struct superblock_disk *disk;

	r = superblock_read_lock(md, &sblock);
	if (r) {
		DMERR("couldn't read_lock superblock");
		return r;
	}

	disk = dm_block_data(sblock);
	r = dm_tm_open_with_sm(md->bm, SUPERBLOCK_LOCATION,
			       disk->metadata_space_map_root,
			       sizeof(disk->metadata_space_map_root),
			       &md->tm, &md->sm);
	if (r) {
		DMERR("dm_tm_open_with_sm failed");
		goto bad;
	}

	setup_infos(md);

	md->block_size = le32_to_cpu(disk->data_block_size);
	md->nr_blocks = le32_to_cpu(disk->nr_blocks);
	md->current_era = le32_to_cpu(disk->current_era);

	md->writeset_tree_root = le64_to_cpu(disk->writeset_tree_root);
	md->era_array_root = le64_to_cpu(disk->era_array_root);
	md->metadata_snap = le64_to_cpu(disk->metadata_snap);
	md->archived_writesets = true;

	dm_bm_unlock(sblock);

	return 0;

bad:
	dm_bm_unlock(sblock);
	return r;
}