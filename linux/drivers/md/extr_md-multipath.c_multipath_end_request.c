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
struct multipath_bh {size_t path; TYPE_3__* mddev; } ;
struct mpconf {int /*<<< orphan*/  mddev; TYPE_1__* multipaths; } ;
struct md_rdev {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {scalar_t__ bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_status; TYPE_2__ bi_iter; struct multipath_bh* bi_private; } ;
struct TYPE_6__ {struct mpconf* private; } ;
struct TYPE_4__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  md_error (TYPE_3__*,struct md_rdev*) ; 
 int /*<<< orphan*/  multipath_end_bh_io (struct multipath_bh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multipath_reschedule_retry (struct multipath_bh*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void multipath_end_request(struct bio *bio)
{
	struct multipath_bh *mp_bh = bio->bi_private;
	struct mpconf *conf = mp_bh->mddev->private;
	struct md_rdev *rdev = conf->multipaths[mp_bh->path].rdev;

	if (!bio->bi_status)
		multipath_end_bh_io(mp_bh, 0);
	else if (!(bio->bi_opf & REQ_RAHEAD)) {
		/*
		 * oops, IO error:
		 */
		char b[BDEVNAME_SIZE];
		md_error (mp_bh->mddev, rdev);
		pr_info("multipath: %s: rescheduling sector %llu\n",
			bdevname(rdev->bdev,b),
			(unsigned long long)bio->bi_iter.bi_sector);
		multipath_reschedule_retry(mp_bh);
	} else
		multipath_end_bh_io(mp_bh, bio->bi_status);
	rdev_dec_pending(rdev, conf->mddev);
}