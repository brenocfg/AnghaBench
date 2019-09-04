#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bi_opf; int /*<<< orphan*/  bi_end_io; } ;
struct r5l_log {TYPE_2__ flush_bio; TYPE_1__* rdev; int /*<<< orphan*/  io_list_lock; int /*<<< orphan*/  flushing_ios; int /*<<< orphan*/  io_end_ios; int /*<<< orphan*/  need_cache_flush; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  bio_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  bio_set_dev (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5l_log_flush_endio ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bio (TYPE_2__*) ; 

void r5l_flush_stripe_to_raid(struct r5l_log *log)
{
	bool do_flush;

	if (!log || !log->need_cache_flush)
		return;

	spin_lock_irq(&log->io_list_lock);
	/* flush bio is running */
	if (!list_empty(&log->flushing_ios)) {
		spin_unlock_irq(&log->io_list_lock);
		return;
	}
	list_splice_tail_init(&log->io_end_ios, &log->flushing_ios);
	do_flush = !list_empty(&log->flushing_ios);
	spin_unlock_irq(&log->io_list_lock);

	if (!do_flush)
		return;
	bio_reset(&log->flush_bio);
	bio_set_dev(&log->flush_bio, log->rdev->bdev);
	log->flush_bio.bi_end_io = r5l_log_flush_endio;
	log->flush_bio.bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
	submit_bio(&log->flush_bio);
}