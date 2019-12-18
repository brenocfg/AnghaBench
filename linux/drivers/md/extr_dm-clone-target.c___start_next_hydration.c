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
struct hash_table_bucket {int dummy; } ;
struct dm_clone_region_hydration {int dummy; } ;
struct clone {unsigned long nr_regions; int /*<<< orphan*/  cmd; } ;
struct batch_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __batch_hydration (struct batch_info*,struct dm_clone_region_hydration*) ; 
 int /*<<< orphan*/  __hash_find (struct hash_table_bucket*,unsigned long) ; 
 int /*<<< orphan*/  __insert_region_hydration (struct hash_table_bucket*,struct dm_clone_region_hydration*) ; 
 struct dm_clone_region_hydration* alloc_hydration (struct clone*) ; 
 int /*<<< orphan*/  bucket_lock_irqsave (struct hash_table_bucket*,unsigned long) ; 
 int /*<<< orphan*/  bucket_unlock_irqrestore (struct hash_table_bucket*,unsigned long) ; 
 unsigned long dm_clone_find_next_unhydrated_region (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dm_clone_is_region_hydrated (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_hydration (struct dm_clone_region_hydration*) ; 
 struct hash_table_bucket* get_hash_table_bucket (struct clone*,unsigned long) ; 
 int /*<<< orphan*/  hydration_init (struct dm_clone_region_hydration*,unsigned long) ; 

__attribute__((used)) static unsigned long __start_next_hydration(struct clone *clone,
					    unsigned long offset,
					    struct batch_info *batch)
{
	unsigned long flags;
	struct hash_table_bucket *bucket;
	struct dm_clone_region_hydration *hd;
	unsigned long nr_regions = clone->nr_regions;

	hd = alloc_hydration(clone);

	/* Try to find a region to hydrate. */
	do {
		offset = dm_clone_find_next_unhydrated_region(clone->cmd, offset);
		if (offset == nr_regions)
			break;

		bucket = get_hash_table_bucket(clone, offset);
		bucket_lock_irqsave(bucket, flags);

		if (!dm_clone_is_region_hydrated(clone->cmd, offset) &&
		    !__hash_find(bucket, offset)) {
			hydration_init(hd, offset);
			__insert_region_hydration(bucket, hd);
			bucket_unlock_irqrestore(bucket, flags);

			/* Batch hydration */
			__batch_hydration(batch, hd);

			return (offset + 1);
		}

		bucket_unlock_irqrestore(bucket, flags);

	} while (++offset < nr_regions);

	if (hd)
		free_hydration(hd);

	return offset;
}