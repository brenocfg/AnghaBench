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
struct clone {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_flush_completions; } ;
struct bio {int bi_opf; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int REQ_FUA ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_worker (struct clone*) ; 

__attribute__((used)) static void complete_overwrite_bio(struct clone *clone, struct bio *bio)
{
	unsigned long flags;

	/*
	 * If the bio has the REQ_FUA flag set we must commit the metadata
	 * before signaling its completion.
	 *
	 * complete_overwrite_bio() is only called by hydration_complete(),
	 * after having successfully updated the metadata. This means we don't
	 * need to call dm_clone_changed_this_transaction() to check if the
	 * metadata has changed and thus we can avoid taking the metadata spin
	 * lock.
	 */
	if (!(bio->bi_opf & REQ_FUA)) {
		bio_endio(bio);
		return;
	}

	/*
	 * If the metadata mode is RO or FAIL we won't be able to commit the
	 * metadata, so we complete the bio with an error.
	 */
	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) {
		bio_io_error(bio);
		return;
	}

	/*
	 * Batch together any bios that trigger commits and then issue a single
	 * commit for them in process_deferred_flush_bios().
	 */
	spin_lock_irqsave(&clone->lock, flags);
	bio_list_add(&clone->deferred_flush_completions, bio);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
}