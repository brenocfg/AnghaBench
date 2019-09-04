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
struct thin_disk_superblock {int /*<<< orphan*/  data_block_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  device_details_root; int /*<<< orphan*/  data_mapping_root; int /*<<< orphan*/  time; } ;
struct dm_pool_metadata {void* data_block_size; void* flags; void* trans_id; void* details_root; void* root; void* time; int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIN_SUPERBLOCK_LOCATION ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_validator ; 

__attribute__((used)) static int __begin_transaction(struct dm_pool_metadata *pmd)
{
	int r;
	struct thin_disk_superblock *disk_super;
	struct dm_block *sblock;

	/*
	 * We re-read the superblock every time.  Shouldn't need to do this
	 * really.
	 */
	r = dm_bm_read_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	pmd->time = le32_to_cpu(disk_super->time);
	pmd->root = le64_to_cpu(disk_super->data_mapping_root);
	pmd->details_root = le64_to_cpu(disk_super->device_details_root);
	pmd->trans_id = le64_to_cpu(disk_super->trans_id);
	pmd->flags = le32_to_cpu(disk_super->flags);
	pmd->data_block_size = le32_to_cpu(disk_super->data_block_size);

	dm_bm_unlock(sblock);
	return 0;
}