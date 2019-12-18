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
struct clone {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_flush_bios; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bio_triggers_commit (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_worker (struct clone*) ; 

__attribute__((used)) static void issue_bio(struct clone *clone, struct bio *bio)
{
	unsigned long flags;

	if (!bio_triggers_commit(clone, bio)) {
		generic_make_request(bio);
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
	bio_list_add(&clone->deferred_flush_bios, bio);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
}