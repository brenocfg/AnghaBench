#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct queue_limits {int max_sectors; scalar_t__ max_write_zeroes_sectors; scalar_t__ max_write_same_sectors; scalar_t__ discard_misaligned; scalar_t__ discard_alignment; scalar_t__ discard_granularity; scalar_t__ max_hw_discard_sectors; scalar_t__ max_discard_sectors; } ;
struct request_queue {TYPE_2__* backing_dev_info; struct queue_limits limits; } ;
struct dm_table {TYPE_1__* md; } ;
struct TYPE_4__ {int io_pages; int /*<<< orphan*/  capabilities; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk; int /*<<< orphan*/  dax_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_STABLE_WRITES ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_DAX ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 unsigned long QUEUE_FLAG_FUA ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  QUEUE_FLAG_SECERASE ; 
 unsigned long QUEUE_FLAG_WC ; 
 scalar_t__ blk_queue_add_random (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ blk_queue_is_zoned (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_write_cache (struct request_queue*,int,int) ; 
 int /*<<< orphan*/  blk_revalidate_disk_zones (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_write_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_dax_synchronous ; 
 int /*<<< orphan*/  device_is_nonrot ; 
 int /*<<< orphan*/  device_is_not_random ; 
 int /*<<< orphan*/  device_supports_dax ; 
 scalar_t__ dm_table_all_devices_attribute (struct dm_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_table_requires_stable_pages (struct dm_table*) ; 
 scalar_t__ dm_table_supports_dax (struct dm_table*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ dm_table_supports_dax_write_cache (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_supports_discards (struct dm_table*) ; 
 scalar_t__ dm_table_supports_flush (struct dm_table*,unsigned long) ; 
 scalar_t__ dm_table_supports_secure_erase (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_supports_write_same (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_supports_write_zeroes (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_verify_integrity (struct dm_table*) ; 
 int /*<<< orphan*/  set_dax_synchronous (int /*<<< orphan*/ ) ; 

void dm_table_set_restrictions(struct dm_table *t, struct request_queue *q,
			       struct queue_limits *limits)
{
	bool wc = false, fua = false;
	int page_size = PAGE_SIZE;

	/*
	 * Copy table's limits to the DM device's request_queue
	 */
	q->limits = *limits;

	if (!dm_table_supports_discards(t)) {
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		/* Must also clear discard limits... */
		q->limits.max_discard_sectors = 0;
		q->limits.max_hw_discard_sectors = 0;
		q->limits.discard_granularity = 0;
		q->limits.discard_alignment = 0;
		q->limits.discard_misaligned = 0;
	} else
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);

	if (dm_table_supports_secure_erase(t))
		blk_queue_flag_set(QUEUE_FLAG_SECERASE, q);

	if (dm_table_supports_flush(t, (1UL << QUEUE_FLAG_WC))) {
		wc = true;
		if (dm_table_supports_flush(t, (1UL << QUEUE_FLAG_FUA)))
			fua = true;
	}
	blk_queue_write_cache(q, wc, fua);

	if (dm_table_supports_dax(t, device_supports_dax, &page_size)) {
		blk_queue_flag_set(QUEUE_FLAG_DAX, q);
		if (dm_table_supports_dax(t, device_dax_synchronous, NULL))
			set_dax_synchronous(t->md->dax_dev);
	}
	else
		blk_queue_flag_clear(QUEUE_FLAG_DAX, q);

	if (dm_table_supports_dax_write_cache(t))
		dax_write_cache(t->md->dax_dev, true);

	/* Ensure that all underlying devices are non-rotational. */
	if (dm_table_all_devices_attribute(t, device_is_nonrot))
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	else
		blk_queue_flag_clear(QUEUE_FLAG_NONROT, q);

	if (!dm_table_supports_write_same(t))
		q->limits.max_write_same_sectors = 0;
	if (!dm_table_supports_write_zeroes(t))
		q->limits.max_write_zeroes_sectors = 0;

	dm_table_verify_integrity(t);

	/*
	 * Some devices don't use blk_integrity but still want stable pages
	 * because they do their own checksumming.
	 */
	if (dm_table_requires_stable_pages(t))
		q->backing_dev_info->capabilities |= BDI_CAP_STABLE_WRITES;
	else
		q->backing_dev_info->capabilities &= ~BDI_CAP_STABLE_WRITES;

	/*
	 * Determine whether or not this queue's I/O timings contribute
	 * to the entropy pool, Only request-based targets use this.
	 * Clear QUEUE_FLAG_ADD_RANDOM if any underlying device does not
	 * have it set.
	 */
	if (blk_queue_add_random(q) && dm_table_all_devices_attribute(t, device_is_not_random))
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, q);

	/*
	 * For a zoned target, the number of zones should be updated for the
	 * correct value to be exposed in sysfs queue/nr_zones. For a BIO based
	 * target, this is all that is needed. For a request based target, the
	 * queue zone bitmaps must also be updated.
	 * Use blk_revalidate_disk_zones() to handle this.
	 */
	if (blk_queue_is_zoned(q))
		blk_revalidate_disk_zones(t->md->disk);

	/* Allow reads to exceed readahead limits */
	q->backing_dev_info->io_pages = limits->max_sectors >> (PAGE_SHIFT - 9);
}