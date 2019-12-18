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
struct r1conf {int raid_disks; int /*<<< orphan*/  mddev; int /*<<< orphan*/  device_lock; TYPE_1__* mirrors; } ;
struct r1bio {size_t read_disk; int /*<<< orphan*/  state; scalar_t__ sector; TYPE_2__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct bio {struct r1bio* bi_private; int /*<<< orphan*/  bi_status; } ;
struct TYPE_4__ {int degraded; struct r1conf* private; } ;
struct TYPE_3__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  FailFast ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  R1BIO_FailFast ; 
 int /*<<< orphan*/  R1BIO_ReadError ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r1bio*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_retry (struct r1bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_head_pos (size_t,struct r1bio*) ; 

__attribute__((used)) static void raid1_end_read_request(struct bio *bio)
{
	int uptodate = !bio->bi_status;
	struct r1bio *r1_bio = bio->bi_private;
	struct r1conf *conf = r1_bio->mddev->private;
	struct md_rdev *rdev = conf->mirrors[r1_bio->read_disk].rdev;

	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	update_head_pos(r1_bio->read_disk, r1_bio);

	if (uptodate)
		set_bit(R1BIO_Uptodate, &r1_bio->state);
	else if (test_bit(FailFast, &rdev->flags) &&
		 test_bit(R1BIO_FailFast, &r1_bio->state))
		/* This was a fail-fast read so we definitely
		 * want to retry */
		;
	else {
		/* If all other devices have failed, we want to return
		 * the error upwards rather than fail the last device.
		 * Here we redefine "uptodate" to mean "Don't want to retry"
		 */
		unsigned long flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		if (r1_bio->mddev->degraded == conf->raid_disks ||
		    (r1_bio->mddev->degraded == conf->raid_disks-1 &&
		     test_bit(In_sync, &rdev->flags)))
			uptodate = 1;
		spin_unlock_irqrestore(&conf->device_lock, flags);
	}

	if (uptodate) {
		raid_end_bio_io(r1_bio);
		rdev_dec_pending(rdev, conf->mddev);
	} else {
		/*
		 * oops, read error:
		 */
		char b[BDEVNAME_SIZE];
		pr_err_ratelimited("md/raid1:%s: %s: rescheduling sector %llu\n",
				   mdname(conf->mddev),
				   bdevname(rdev->bdev, b),
				   (unsigned long long)r1_bio->sector);
		set_bit(R1BIO_ReadError, &r1_bio->state);
		reschedule_retry(r1_bio);
		/* don't drop the reference on read_disk yet */
	}
}