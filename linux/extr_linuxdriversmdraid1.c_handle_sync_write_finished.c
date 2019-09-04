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
struct r1conf {int raid_disks; int /*<<< orphan*/  mddev; TYPE_1__* mirrors; } ;
struct r1bio {int sectors; int /*<<< orphan*/  sector; int /*<<< orphan*/  state; struct bio** bios; } ;
struct md_rdev {int dummy; } ;
struct bio {scalar_t__ bi_status; int /*<<< orphan*/ * bi_end_io; } ;
struct TYPE_2__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  R1BIO_MadeGood ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 int /*<<< orphan*/  md_done_sync (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  md_error (int /*<<< orphan*/ ,struct md_rdev*) ; 
 int /*<<< orphan*/  put_buf (struct r1bio*) ; 
 int /*<<< orphan*/  rdev_clear_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_sync_write_finished(struct r1conf *conf, struct r1bio *r1_bio)
{
	int m;
	int s = r1_bio->sectors;
	for (m = 0; m < conf->raid_disks * 2 ; m++) {
		struct md_rdev *rdev = conf->mirrors[m].rdev;
		struct bio *bio = r1_bio->bios[m];
		if (bio->bi_end_io == NULL)
			continue;
		if (!bio->bi_status &&
		    test_bit(R1BIO_MadeGood, &r1_bio->state)) {
			rdev_clear_badblocks(rdev, r1_bio->sector, s, 0);
		}
		if (bio->bi_status &&
		    test_bit(R1BIO_WriteError, &r1_bio->state)) {
			if (!rdev_set_badblocks(rdev, r1_bio->sector, s, 0))
				md_error(conf->mddev, rdev);
		}
	}
	put_buf(r1_bio);
	md_done_sync(conf->mddev, s, 1);
}