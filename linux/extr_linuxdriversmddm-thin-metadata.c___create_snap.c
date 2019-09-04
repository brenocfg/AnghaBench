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
struct dm_pool_metadata {int /*<<< orphan*/  details_root; int /*<<< orphan*/  details_info; int /*<<< orphan*/  root; int /*<<< orphan*/  tl_info; int /*<<< orphan*/  time; int /*<<< orphan*/  tm; } ;
struct disk_device_details {int dummy; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  struct disk_device_details __le64 ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  __close_device (struct dm_thin_device*) ; 
 int /*<<< orphan*/  __dm_bless_for_disk (struct disk_device_details*) ; 
 int __open_device (struct dm_pool_metadata*,int /*<<< orphan*/ ,int,struct dm_thin_device**) ; 
 int __set_snapshot_details (struct dm_pool_metadata*,struct dm_thin_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct disk_device_details cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct disk_device_details*,int /*<<< orphan*/ *) ; 
 int dm_btree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct disk_device_details*) ; 
 int /*<<< orphan*/  dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (struct disk_device_details) ; 

__attribute__((used)) static int __create_snap(struct dm_pool_metadata *pmd,
			 dm_thin_id dev, dm_thin_id origin)
{
	int r;
	dm_block_t origin_root;
	uint64_t key = origin, dev_key = dev;
	struct dm_thin_device *td;
	struct disk_device_details details_le;
	__le64 value;

	/* check this device is unused */
	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &dev_key, &details_le);
	if (!r)
		return -EEXIST;

	/* find the mapping tree for the origin */
	r = dm_btree_lookup(&pmd->tl_info, pmd->root, &key, &value);
	if (r)
		return r;
	origin_root = le64_to_cpu(value);

	/* clone the origin, an inc will do */
	dm_tm_inc(pmd->tm, origin_root);

	/* insert into the main mapping tree */
	value = cpu_to_le64(origin_root);
	__dm_bless_for_disk(&value);
	key = dev;
	r = dm_btree_insert(&pmd->tl_info, pmd->root, &key, &value, &pmd->root);
	if (r) {
		dm_tm_dec(pmd->tm, origin_root);
		return r;
	}

	pmd->time++;

	r = __open_device(pmd, dev, 1, &td);
	if (r)
		goto bad;

	r = __set_snapshot_details(pmd, td, origin, pmd->time);
	__close_device(td);

	if (r)
		goto bad;

	return 0;

bad:
	dm_btree_remove(&pmd->tl_info, pmd->root, &key, &pmd->root);
	dm_btree_remove(&pmd->details_info, pmd->details_root,
			&key, &pmd->details_root);
	return r;
}