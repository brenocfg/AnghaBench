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
struct r10conf {int /*<<< orphan*/  mddev; } ;
struct r10bio {int read_slot; int /*<<< orphan*/  state; scalar_t__ sector; TYPE_2__* devs; TYPE_1__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  raid_disk; } ;
struct bio {struct r10bio* bi_private; int /*<<< orphan*/  bi_status; } ;
struct TYPE_4__ {struct md_rdev* rdev; } ;
struct TYPE_3__ {struct r10conf* private; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  R10BIO_Previous ; 
 int /*<<< orphan*/  R10BIO_ReadError ; 
 int /*<<< orphan*/  R10BIO_Uptodate ; 
 int /*<<< orphan*/  _enough (struct r10conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r10bio*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_retry (struct r10bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_head_pos (int,struct r10bio*) ; 

__attribute__((used)) static void raid10_end_read_request(struct bio *bio)
{
	int uptodate = !bio->bi_status;
	struct r10bio *r10_bio = bio->bi_private;
	int slot;
	struct md_rdev *rdev;
	struct r10conf *conf = r10_bio->mddev->private;

	slot = r10_bio->read_slot;
	rdev = r10_bio->devs[slot].rdev;
	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	update_head_pos(slot, r10_bio);

	if (uptodate) {
		/*
		 * Set R10BIO_Uptodate in our master bio, so that
		 * we will return a good error code to the higher
		 * levels even if IO on some other mirrored buffer fails.
		 *
		 * The 'master' represents the composite IO operation to
		 * user-side. So if something waits for IO, then it will
		 * wait for the 'master' bio.
		 */
		set_bit(R10BIO_Uptodate, &r10_bio->state);
	} else {
		/* If all other devices that store this block have
		 * failed, we want to return the error upwards rather
		 * than fail the last device.  Here we redefine
		 * "uptodate" to mean "Don't want to retry"
		 */
		if (!_enough(conf, test_bit(R10BIO_Previous, &r10_bio->state),
			     rdev->raid_disk))
			uptodate = 1;
	}
	if (uptodate) {
		raid_end_bio_io(r10_bio);
		rdev_dec_pending(rdev, conf->mddev);
	} else {
		/*
		 * oops, read error - keep the refcount on the rdev
		 */
		char b[BDEVNAME_SIZE];
		pr_err_ratelimited("md/raid10:%s: %s: rescheduling sector %llu\n",
				   mdname(conf->mddev),
				   bdevname(rdev->bdev, b),
				   (unsigned long long)r10_bio->sector);
		set_bit(R10BIO_ReadError, &r10_bio->state);
		reschedule_retry(r10_bio);
	}
}