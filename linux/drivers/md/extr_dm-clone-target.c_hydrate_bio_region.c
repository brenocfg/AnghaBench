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
struct dm_clone_region_hydration {int /*<<< orphan*/  deferred_bios; int /*<<< orphan*/  h; } ;
struct clone {int /*<<< orphan*/  cmd; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 struct dm_clone_region_hydration* __find_or_insert_region_hydration (struct hash_table_bucket*,struct dm_clone_region_hydration*) ; 
 struct dm_clone_region_hydration* __hash_find (struct hash_table_bucket*,unsigned long) ; 
 struct dm_clone_region_hydration* alloc_hydration (struct clone*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 unsigned long bio_to_region (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  bucket_lock_irqsave (struct hash_table_bucket*,unsigned long) ; 
 int /*<<< orphan*/  bucket_unlock_irqrestore (struct hash_table_bucket*,unsigned long) ; 
 scalar_t__ dm_clone_is_region_hydrated (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_hydration (struct dm_clone_region_hydration*) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 struct hash_table_bucket* get_hash_table_bucket (struct clone*,unsigned long) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hydration_copy (struct dm_clone_region_hydration*,int) ; 
 int /*<<< orphan*/  hydration_init (struct dm_clone_region_hydration*,unsigned long) ; 
 int /*<<< orphan*/  hydration_overwrite (struct dm_clone_region_hydration*,struct bio*) ; 
 scalar_t__ is_overwrite_bio (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  issue_bio (struct clone*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hydrate_bio_region(struct clone *clone, struct bio *bio)
{
	unsigned long flags;
	unsigned long region_nr;
	struct hash_table_bucket *bucket;
	struct dm_clone_region_hydration *hd, *hd2;

	region_nr = bio_to_region(clone, bio);
	bucket = get_hash_table_bucket(clone, region_nr);

	bucket_lock_irqsave(bucket, flags);

	hd = __hash_find(bucket, region_nr);
	if (hd) {
		/* Someone else is hydrating the region */
		bio_list_add(&hd->deferred_bios, bio);
		bucket_unlock_irqrestore(bucket, flags);
		return;
	}

	if (dm_clone_is_region_hydrated(clone->cmd, region_nr)) {
		/* The region has been hydrated */
		bucket_unlock_irqrestore(bucket, flags);
		issue_bio(clone, bio);
		return;
	}

	/*
	 * We must allocate a hydration descriptor and start the hydration of
	 * the corresponding region.
	 */
	bucket_unlock_irqrestore(bucket, flags);

	hd = alloc_hydration(clone);
	hydration_init(hd, region_nr);

	bucket_lock_irqsave(bucket, flags);

	/* Check if the region has been hydrated in the meantime. */
	if (dm_clone_is_region_hydrated(clone->cmd, region_nr)) {
		bucket_unlock_irqrestore(bucket, flags);
		free_hydration(hd);
		issue_bio(clone, bio);
		return;
	}

	hd2 = __find_or_insert_region_hydration(bucket, hd);
	if (hd2 != hd) {
		/* Someone else started the region's hydration. */
		bio_list_add(&hd2->deferred_bios, bio);
		bucket_unlock_irqrestore(bucket, flags);
		free_hydration(hd);
		return;
	}

	/*
	 * If the metadata mode is RO or FAIL then there is no point starting a
	 * hydration, since we will not be able to update the metadata when the
	 * hydration finishes.
	 */
	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) {
		hlist_del(&hd->h);
		bucket_unlock_irqrestore(bucket, flags);
		free_hydration(hd);
		bio_io_error(bio);
		return;
	}

	/*
	 * Start region hydration.
	 *
	 * If a bio overwrites a region, i.e., its size is equal to the
	 * region's size, then we don't need to copy the region from the source
	 * to the destination device.
	 */
	if (is_overwrite_bio(clone, bio)) {
		bucket_unlock_irqrestore(bucket, flags);
		hydration_overwrite(hd, bio);
	} else {
		bio_list_add(&hd->deferred_bios, bio);
		bucket_unlock_irqrestore(bucket, flags);
		hydration_copy(hd, 1);
	}
}