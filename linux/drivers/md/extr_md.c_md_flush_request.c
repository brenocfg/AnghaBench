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
struct mddev {TYPE_2__* pers; int /*<<< orphan*/  flush_work; int /*<<< orphan*/  lock; struct bio* flush_bio; int /*<<< orphan*/  last_flush; int /*<<< orphan*/  sb_wait; } ;
struct TYPE_3__ {scalar_t__ bi_size; } ;
struct bio {int /*<<< orphan*/  bi_opf; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* make_request ) (struct mddev*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int /*<<< orphan*/  WARN_ON (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  md_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  submit_flushes ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void md_flush_request(struct mddev *mddev, struct bio *bio)
{
	ktime_t start = ktime_get_boottime();
	spin_lock_irq(&mddev->lock);
	wait_event_lock_irq(mddev->sb_wait,
			    !mddev->flush_bio ||
			    ktime_after(mddev->last_flush, start),
			    mddev->lock);
	if (!ktime_after(mddev->last_flush, start)) {
		WARN_ON(mddev->flush_bio);
		mddev->flush_bio = bio;
		bio = NULL;
	}
	spin_unlock_irq(&mddev->lock);

	if (!bio) {
		INIT_WORK(&mddev->flush_work, submit_flushes);
		queue_work(md_wq, &mddev->flush_work);
	} else {
		/* flush was performed for some other bio while we waited. */
		if (bio->bi_iter.bi_size == 0)
			/* an empty barrier - all done */
			bio_endio(bio);
		else {
			bio->bi_opf &= ~REQ_PREFLUSH;
			mddev->pers->make_request(mddev, bio);
		}
	}
}