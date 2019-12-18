#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r10conf {int copies; TYPE_3__* mddev; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  nr_queued; int /*<<< orphan*/  bio_end_io_list; TYPE_1__* mirrors; } ;
struct r10bio {int /*<<< orphan*/  state; int /*<<< orphan*/  retry_list; int /*<<< orphan*/  sectors; TYPE_2__* devs; } ;
struct md_rdev {int dummy; } ;
struct bio {scalar_t__ bi_status; int /*<<< orphan*/ * bi_end_io; } ;
struct TYPE_7__ {int /*<<< orphan*/  thread; } ;
struct TYPE_6__ {int devnum; int /*<<< orphan*/  addr; struct bio* repl_bio; struct bio* bio; } ;
struct TYPE_5__ {struct md_rdev* replacement; struct md_rdev* rdev; } ;

/* Variables and functions */
 struct bio* IO_MADE_GOOD ; 
 int /*<<< orphan*/  R10BIO_Degraded ; 
 int /*<<< orphan*/  R10BIO_IsRecover ; 
 int /*<<< orphan*/  R10BIO_IsSync ; 
 int /*<<< orphan*/  R10BIO_WriteError ; 
 int /*<<< orphan*/  close_write (struct r10bio*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_error (TYPE_3__*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  narrow_write_error (struct r10bio*,int) ; 
 int /*<<< orphan*/  put_buf (struct r10bio*) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r10bio*) ; 
 int /*<<< orphan*/  rdev_clear_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_3__*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_write_completed(struct r10conf *conf, struct r10bio *r10_bio)
{
	/* Some sort of write request has finished and it
	 * succeeded in writing where we thought there was a
	 * bad block.  So forget the bad block.
	 * Or possibly if failed and we need to record
	 * a bad block.
	 */
	int m;
	struct md_rdev *rdev;

	if (test_bit(R10BIO_IsSync, &r10_bio->state) ||
	    test_bit(R10BIO_IsRecover, &r10_bio->state)) {
		for (m = 0; m < conf->copies; m++) {
			int dev = r10_bio->devs[m].devnum;
			rdev = conf->mirrors[dev].rdev;
			if (r10_bio->devs[m].bio == NULL ||
				r10_bio->devs[m].bio->bi_end_io == NULL)
				continue;
			if (!r10_bio->devs[m].bio->bi_status) {
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
			} else {
				if (!rdev_set_badblocks(
					    rdev,
					    r10_bio->devs[m].addr,
					    r10_bio->sectors, 0))
					md_error(conf->mddev, rdev);
			}
			rdev = conf->mirrors[dev].replacement;
			if (r10_bio->devs[m].repl_bio == NULL ||
				r10_bio->devs[m].repl_bio->bi_end_io == NULL)
				continue;

			if (!r10_bio->devs[m].repl_bio->bi_status) {
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
			} else {
				if (!rdev_set_badblocks(
					    rdev,
					    r10_bio->devs[m].addr,
					    r10_bio->sectors, 0))
					md_error(conf->mddev, rdev);
			}
		}
		put_buf(r10_bio);
	} else {
		bool fail = false;
		for (m = 0; m < conf->copies; m++) {
			int dev = r10_bio->devs[m].devnum;
			struct bio *bio = r10_bio->devs[m].bio;
			rdev = conf->mirrors[dev].rdev;
			if (bio == IO_MADE_GOOD) {
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
				rdev_dec_pending(rdev, conf->mddev);
			} else if (bio != NULL && bio->bi_status) {
				fail = true;
				if (!narrow_write_error(r10_bio, m)) {
					md_error(conf->mddev, rdev);
					set_bit(R10BIO_Degraded,
						&r10_bio->state);
				}
				rdev_dec_pending(rdev, conf->mddev);
			}
			bio = r10_bio->devs[m].repl_bio;
			rdev = conf->mirrors[dev].replacement;
			if (rdev && bio == IO_MADE_GOOD) {
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
				rdev_dec_pending(rdev, conf->mddev);
			}
		}
		if (fail) {
			spin_lock_irq(&conf->device_lock);
			list_add(&r10_bio->retry_list, &conf->bio_end_io_list);
			conf->nr_queued++;
			spin_unlock_irq(&conf->device_lock);
			/*
			 * In case freeze_array() is waiting for condition
			 * nr_pending == nr_queued + extra to be true.
			 */
			wake_up(&conf->wait_barrier);
			md_wakeup_thread(conf->mddev->thread);
		} else {
			if (test_bit(R10BIO_WriteError,
				     &r10_bio->state))
				close_write(r10_bio);
			raid_end_bio_io(r10_bio);
		}
	}
}