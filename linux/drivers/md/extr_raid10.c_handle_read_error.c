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
struct r10conf {int dummy; } ;
struct r10bio {int read_slot; int /*<<< orphan*/  master_bio; scalar_t__ state; TYPE_1__* devs; } ;
struct mddev {scalar_t__ ro; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct bio* bio; struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FailFast ; 
 struct bio* IO_BLOCKED ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  fix_read_error (struct r10conf*,struct mddev*,struct r10bio*) ; 
 int /*<<< orphan*/  freeze_array (struct r10conf*,int) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  raid10_read_request (struct mddev*,int /*<<< orphan*/ ,struct r10bio*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unfreeze_array (struct r10conf*) ; 

__attribute__((used)) static void handle_read_error(struct mddev *mddev, struct r10bio *r10_bio)
{
	int slot = r10_bio->read_slot;
	struct bio *bio;
	struct r10conf *conf = mddev->private;
	struct md_rdev *rdev = r10_bio->devs[slot].rdev;

	/* we got a read error. Maybe the drive is bad.  Maybe just
	 * the block and we can fix it.
	 * We freeze all other IO, and try reading the block from
	 * other devices.  When we find one, we re-write
	 * and check it that fixes the read error.
	 * This is all done synchronously while the array is
	 * frozen.
	 */
	bio = r10_bio->devs[slot].bio;
	bio_put(bio);
	r10_bio->devs[slot].bio = NULL;

	if (mddev->ro)
		r10_bio->devs[slot].bio = IO_BLOCKED;
	else if (!test_bit(FailFast, &rdev->flags)) {
		freeze_array(conf, 1);
		fix_read_error(conf, mddev, r10_bio);
		unfreeze_array(conf);
	} else
		md_error(mddev, rdev);

	rdev_dec_pending(rdev, mddev);
	allow_barrier(conf);
	r10_bio->state = 0;
	raid10_read_request(mddev, r10_bio->master_bio, r10_bio);
}