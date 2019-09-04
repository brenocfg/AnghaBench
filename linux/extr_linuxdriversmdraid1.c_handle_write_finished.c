#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r1conf {int raid_disks; TYPE_2__* mddev; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  device_lock; int /*<<< orphan*/ * nr_queued; int /*<<< orphan*/  bio_end_io_list; TYPE_1__* mirrors; } ;
struct r1bio {int /*<<< orphan*/  state; int /*<<< orphan*/  sector; int /*<<< orphan*/  retry_list; int /*<<< orphan*/ ** bios; int /*<<< orphan*/  sectors; } ;
struct md_rdev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  thread; } ;
struct TYPE_4__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IO_MADE_GOOD ; 
 int /*<<< orphan*/  R1BIO_Degraded ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_write (struct r1bio*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_error (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  narrow_write_error (struct r1bio*,int) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r1bio*) ; 
 int /*<<< orphan*/  rdev_clear_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_2__*) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_write_finished(struct r1conf *conf, struct r1bio *r1_bio)
{
	int m, idx;
	bool fail = false;

	for (m = 0; m < conf->raid_disks * 2 ; m++)
		if (r1_bio->bios[m] == IO_MADE_GOOD) {
			struct md_rdev *rdev = conf->mirrors[m].rdev;
			rdev_clear_badblocks(rdev,
					     r1_bio->sector,
					     r1_bio->sectors, 0);
			rdev_dec_pending(rdev, conf->mddev);
		} else if (r1_bio->bios[m] != NULL) {
			/* This drive got a write error.  We need to
			 * narrow down and record precise write
			 * errors.
			 */
			fail = true;
			if (!narrow_write_error(r1_bio, m)) {
				md_error(conf->mddev,
					 conf->mirrors[m].rdev);
				/* an I/O failed, we can't clear the bitmap */
				set_bit(R1BIO_Degraded, &r1_bio->state);
			}
			rdev_dec_pending(conf->mirrors[m].rdev,
					 conf->mddev);
		}
	if (fail) {
		spin_lock_irq(&conf->device_lock);
		list_add(&r1_bio->retry_list, &conf->bio_end_io_list);
		idx = sector_to_idx(r1_bio->sector);
		atomic_inc(&conf->nr_queued[idx]);
		spin_unlock_irq(&conf->device_lock);
		/*
		 * In case freeze_array() is waiting for condition
		 * get_unqueued_pending() == extra to be true.
		 */
		wake_up(&conf->wait_barrier);
		md_wakeup_thread(conf->mddev->thread);
	} else {
		if (test_bit(R1BIO_WriteError, &r1_bio->state))
			close_write(r1_bio);
		raid_end_bio_io(r1_bio);
	}
}