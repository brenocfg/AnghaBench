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
struct request_queue {int /*<<< orphan*/  make_request_fn; } ;
struct block_device {int /*<<< orphan*/ * bd_disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENXIO ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int submit_bio_wait (struct bio*) ; 

int blkdev_issue_flush(struct block_device *bdev, gfp_t gfp_mask,
		sector_t *error_sector)
{
	struct request_queue *q;
	struct bio *bio;
	int ret = 0;

	if (bdev->bd_disk == NULL)
		return -ENXIO;

	q = bdev_get_queue(bdev);
	if (!q)
		return -ENXIO;

	/*
	 * some block devices may not have their queue correctly set up here
	 * (e.g. loop device without a backing file) and so issuing a flush
	 * here will panic. Ensure there is a request function before issuing
	 * the flush.
	 */
	if (!q->make_request_fn)
		return -ENXIO;

	bio = bio_alloc(gfp_mask, 0);
	bio_set_dev(bio, bdev);
	bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;

	ret = submit_bio_wait(bio);

	/*
	 * The driver must store the error location in ->bi_sector, if
	 * it supports it. For non-stacked drivers, this should be
	 * copied from blk_rq_pos(rq).
	 */
	if (error_sector)
		*error_sector = bio->bi_iter.bi_sector;

	bio_put(bio);
	return ret;
}