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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_thin_device {int dummy; } ;
struct dm_pool_metadata {int /*<<< orphan*/  bl_info; int /*<<< orphan*/  root; int /*<<< orphan*/  tl_info; int /*<<< orphan*/  details_root; int /*<<< orphan*/  details_info; } ;
struct disk_device_details {int dummy; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  __close_device (struct dm_thin_device*) ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int __open_device (struct dm_pool_metadata*,int /*<<< orphan*/ ,int,struct dm_thin_device**) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_btree_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dm_btree_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct disk_device_details*) ; 
 int /*<<< orphan*/  dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __create_thin(struct dm_pool_metadata *pmd,
			 dm_thin_id dev)
{
	int r;
	dm_block_t dev_root;
	uint64_t key = dev;
	struct disk_device_details details_le;
	struct dm_thin_device *td;
	__le64 value;

	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &key, &details_le);
	if (!r)
		return -EEXIST;

	/*
	 * Create an empty btree for the mappings.
	 */
	r = dm_btree_empty(&pmd->bl_info, &dev_root);
	if (r)
		return r;

	/*
	 * Insert it into the main mapping tree.
	 */
	value = cpu_to_le64(dev_root);
	__dm_bless_for_disk(&value);
	r = dm_btree_insert(&pmd->tl_info, pmd->root, &key, &value, &pmd->root);
	if (r) {
		dm_btree_del(&pmd->bl_info, dev_root);
		return r;
	}

	r = __open_device(pmd, dev, 1, &td);
	if (r) {
		dm_btree_remove(&pmd->tl_info, pmd->root, &key, &pmd->root);
		dm_btree_del(&pmd->bl_info, dev_root);
		return r;
	}
	__close_device(td);

	return r;
}