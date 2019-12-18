#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dm_integrity_c {int synchronous_mode; TYPE_1__ endio_wait; int /*<<< orphan*/  bitmap_flush_work; int /*<<< orphan*/  commit_wq; int /*<<< orphan*/  synchronous_bios; } ;
struct bio {scalar_t__ bi_status; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int dm_integrity_failed (struct dm_integrity_c*) ; 
 scalar_t__ errno_to_blk_status (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_endio(struct dm_integrity_c *ic, struct bio *bio)
{
	int r = dm_integrity_failed(ic);
	if (unlikely(r) && !bio->bi_status)
		bio->bi_status = errno_to_blk_status(r);
	if (unlikely(ic->synchronous_mode) && bio_op(bio) == REQ_OP_WRITE) {
		unsigned long flags;
		spin_lock_irqsave(&ic->endio_wait.lock, flags);
		bio_list_add(&ic->synchronous_bios, bio);
		queue_delayed_work(ic->commit_wq, &ic->bitmap_flush_work, 0);
		spin_unlock_irqrestore(&ic->endio_wait.lock, flags);
		return;
	}
	bio_endio(bio);
}