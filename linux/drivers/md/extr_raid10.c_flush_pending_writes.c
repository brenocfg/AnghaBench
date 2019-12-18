#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ head; } ;
struct r10conf {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_barrier; TYPE_1__* mddev; scalar_t__ pending_count; TYPE_3__ pending_bio_list; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct blk_plug {int dummy; } ;
struct bio {TYPE_2__* bi_disk; struct bio* bi_next; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 struct bio* bio_list_get (TYPE_3__*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  md_bitmap_unplug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_pending_writes(struct r10conf *conf)
{
	/* Any writes that have been queued but are awaiting
	 * bitmap updates get flushed here.
	 */
	spin_lock_irq(&conf->device_lock);

	if (conf->pending_bio_list.head) {
		struct blk_plug plug;
		struct bio *bio;

		bio = bio_list_get(&conf->pending_bio_list);
		conf->pending_count = 0;
		spin_unlock_irq(&conf->device_lock);

		/*
		 * As this is called in a wait_event() loop (see freeze_array),
		 * current->state might be TASK_UNINTERRUPTIBLE which will
		 * cause a warning when we prepare to wait again.  As it is
		 * rare that this path is taken, it is perfectly safe to force
		 * us to go around the wait_event() loop again, so the warning
		 * is a false-positive. Silence the warning by resetting
		 * thread state
		 */
		__set_current_state(TASK_RUNNING);

		blk_start_plug(&plug);
		/* flush any pending bitmap writes to disk
		 * before proceeding w/ I/O */
		md_bitmap_unplug(conf->mddev->bitmap);
		wake_up(&conf->wait_barrier);

		while (bio) { /* submit pending writes */
			struct bio *next = bio->bi_next;
			struct md_rdev *rdev = (void*)bio->bi_disk;
			bio->bi_next = NULL;
			bio_set_dev(bio, rdev->bdev);
			if (test_bit(Faulty, &rdev->flags)) {
				bio_io_error(bio);
			} else if (unlikely((bio_op(bio) ==  REQ_OP_DISCARD) &&
					    !blk_queue_discard(bio->bi_disk->queue)))
				/* Just ignore it */
				bio_endio(bio);
			else
				generic_make_request(bio);
			bio = next;
		}
		blk_finish_plug(&plug);
	} else
		spin_unlock_irq(&conf->device_lock);
}