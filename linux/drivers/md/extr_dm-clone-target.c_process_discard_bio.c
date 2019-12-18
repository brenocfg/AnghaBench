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
struct clone {unsigned long nr_regions; int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_discard_bios; int /*<<< orphan*/  cmd; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bio_region_range (struct clone*,struct bio*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  complete_discard_bio (struct clone*,struct bio*,int) ; 
 scalar_t__ dm_clone_is_range_hydrated (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_worker (struct clone*) ; 

__attribute__((used)) static void process_discard_bio(struct clone *clone, struct bio *bio)
{
	unsigned long rs, re, flags;

	bio_region_range(clone, bio, &rs, &re);
	BUG_ON(re > clone->nr_regions);

	if (unlikely(rs == re)) {
		bio_endio(bio);
		return;
	}

	/*
	 * The covered regions are already hydrated so we just need to pass
	 * down the discard.
	 */
	if (dm_clone_is_range_hydrated(clone->cmd, rs, re - rs)) {
		complete_discard_bio(clone, bio, true);
		return;
	}

	/*
	 * If the metadata mode is RO or FAIL we won't be able to update the
	 * metadata for the regions covered by the discard so we just ignore
	 * it.
	 */
	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) {
		bio_endio(bio);
		return;
	}

	/*
	 * Defer discard processing.
	 */
	spin_lock_irqsave(&clone->lock, flags);
	bio_list_add(&clone->deferred_discard_bios, bio);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
}