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
struct thin_c {int /*<<< orphan*/  td; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_flush_bios; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bio_triggers_commit (struct thin_c*,struct bio*) ; 
 scalar_t__ dm_thin_aborted_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void issue(struct thin_c *tc, struct bio *bio)
{
	struct pool *pool = tc->pool;
	unsigned long flags;

	if (!bio_triggers_commit(tc, bio)) {
		generic_make_request(bio);
		return;
	}

	/*
	 * Complete bio with an error if earlier I/O caused changes to
	 * the metadata that can't be committed e.g, due to I/O errors
	 * on the metadata device.
	 */
	if (dm_thin_aborted_changes(tc->td)) {
		bio_io_error(bio);
		return;
	}

	/*
	 * Batch together any bios that trigger commits and then issue a
	 * single commit for them in process_deferred_bios().
	 */
	spin_lock_irqsave(&pool->lock, flags);
	bio_list_add(&pool->deferred_flush_bios, bio);
	spin_unlock_irqrestore(&pool->lock, flags);
}