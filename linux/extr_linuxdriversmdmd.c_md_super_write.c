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
struct page {int dummy; } ;
struct mddev {int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  flags; } ;
struct md_rdev {int /*<<< orphan*/  flags; scalar_t__ bdev; scalar_t__ meta_bdev; int /*<<< orphan*/  nr_pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_end_io; struct md_rdev* bi_private; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  FailFast ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  LastDev ; 
 int MD_FAILFAST ; 
 int /*<<< orphan*/  MD_FAILFAST_SUPPORTED ; 
 int REQ_FUA ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,scalar_t__) ; 
 struct bio* md_bio_alloc_sync (struct mddev*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  super_written ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void md_super_write(struct mddev *mddev, struct md_rdev *rdev,
		   sector_t sector, int size, struct page *page)
{
	/* write first size bytes of page to sector of rdev
	 * Increment mddev->pending_writes before returning
	 * and decrement it on completion, waking up sb_wait
	 * if zero is reached.
	 * If an error occurred, call md_error
	 */
	struct bio *bio;
	int ff = 0;

	if (!page)
		return;

	if (test_bit(Faulty, &rdev->flags))
		return;

	bio = md_bio_alloc_sync(mddev);

	atomic_inc(&rdev->nr_pending);

	bio_set_dev(bio, rdev->meta_bdev ? rdev->meta_bdev : rdev->bdev);
	bio->bi_iter.bi_sector = sector;
	bio_add_page(bio, page, size, 0);
	bio->bi_private = rdev;
	bio->bi_end_io = super_written;

	if (test_bit(MD_FAILFAST_SUPPORTED, &mddev->flags) &&
	    test_bit(FailFast, &rdev->flags) &&
	    !test_bit(LastDev, &rdev->flags))
		ff = MD_FAILFAST;
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_PREFLUSH | REQ_FUA | ff;

	atomic_inc(&mddev->pending_writes);
	submit_bio(bio);
}