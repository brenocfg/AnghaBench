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
struct mddev {int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  sb_flags; } ;
struct md_rdev {int /*<<< orphan*/  flags; struct mddev* mddev; } ;
struct bio {int bi_opf; scalar_t__ bi_status; struct md_rdev* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  LastDev ; 
 int MD_FAILFAST ; 
 int /*<<< orphan*/  MD_SB_NEED_REWRITE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void super_written(struct bio *bio)
{
	struct md_rdev *rdev = bio->bi_private;
	struct mddev *mddev = rdev->mddev;

	if (bio->bi_status) {
		pr_err("md: super_written gets error=%d\n", bio->bi_status);
		md_error(mddev, rdev);
		if (!test_bit(Faulty, &rdev->flags)
		    && (bio->bi_opf & MD_FAILFAST)) {
			set_bit(MD_SB_NEED_REWRITE, &mddev->sb_flags);
			set_bit(LastDev, &rdev->flags);
		}
	} else
		clear_bit(LastDev, &rdev->flags);

	if (atomic_dec_and_test(&mddev->pending_writes))
		wake_up(&mddev->sb_wait);
	rdev_dec_pending(rdev, mddev);
	bio_put(bio);
}