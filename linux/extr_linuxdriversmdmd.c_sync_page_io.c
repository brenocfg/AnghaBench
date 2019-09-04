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
struct page {int dummy; } ;
struct md_rdev {scalar_t__ sb_start; scalar_t__ new_data_offset; scalar_t__ data_offset; TYPE_2__* mddev; int /*<<< orphan*/  bdev; int /*<<< orphan*/  meta_bdev; } ;
struct TYPE_3__ {scalar_t__ bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_status; TYPE_1__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {scalar_t__ reshape_position; int reshape_backwards; } ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 struct bio* md_bio_alloc_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  submit_bio_wait (struct bio*) ; 

int sync_page_io(struct md_rdev *rdev, sector_t sector, int size,
		 struct page *page, int op, int op_flags, bool metadata_op)
{
	struct bio *bio = md_bio_alloc_sync(rdev->mddev);
	int ret;

	if (metadata_op && rdev->meta_bdev)
		bio_set_dev(bio, rdev->meta_bdev);
	else
		bio_set_dev(bio, rdev->bdev);
	bio_set_op_attrs(bio, op, op_flags);
	if (metadata_op)
		bio->bi_iter.bi_sector = sector + rdev->sb_start;
	else if (rdev->mddev->reshape_position != MaxSector &&
		 (rdev->mddev->reshape_backwards ==
		  (sector >= rdev->mddev->reshape_position)))
		bio->bi_iter.bi_sector = sector + rdev->new_data_offset;
	else
		bio->bi_iter.bi_sector = sector + rdev->data_offset;
	bio_add_page(bio, page, size, 0);

	submit_bio_wait(bio);

	ret = !bio->bi_status;
	bio_put(bio);
	return ret;
}