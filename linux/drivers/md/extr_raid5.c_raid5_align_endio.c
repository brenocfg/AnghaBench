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
struct r5conf {int /*<<< orphan*/  wait_for_quiescent; int /*<<< orphan*/  active_aligned_reads; int /*<<< orphan*/  mddev; } ;
struct mddev {struct r5conf* private; } ;
struct md_rdev {struct mddev* mddev; } ;
struct bio {int /*<<< orphan*/ * bi_next; int /*<<< orphan*/  bi_status; struct bio* bi_private; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_bio_to_retry (struct bio*,struct r5conf*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5_align_endio(struct bio *bi)
{
	struct bio* raid_bi  = bi->bi_private;
	struct mddev *mddev;
	struct r5conf *conf;
	struct md_rdev *rdev;
	blk_status_t error = bi->bi_status;

	bio_put(bi);

	rdev = (void*)raid_bi->bi_next;
	raid_bi->bi_next = NULL;
	mddev = rdev->mddev;
	conf = mddev->private;

	rdev_dec_pending(rdev, conf->mddev);

	if (!error) {
		bio_endio(raid_bi);
		if (atomic_dec_and_test(&conf->active_aligned_reads))
			wake_up(&conf->wait_for_quiescent);
		return;
	}

	pr_debug("raid5_align_endio : io error...handing IO for a retry\n");

	add_bio_to_retry(raid_bi, conf);
}