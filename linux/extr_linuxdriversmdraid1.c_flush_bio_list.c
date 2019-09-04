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
struct r1conf {int /*<<< orphan*/  wait_barrier; TYPE_2__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct bio {TYPE_1__* bi_disk; struct bio* bi_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  md_bitmap_unplug (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_bio_list(struct r1conf *conf, struct bio *bio)
{
	/* flush any pending bitmap writes to disk before proceeding w/ I/O */
	md_bitmap_unplug(conf->mddev->bitmap);
	wake_up(&conf->wait_barrier);

	while (bio) { /* submit pending writes */
		struct bio *next = bio->bi_next;
		struct md_rdev *rdev = (void *)bio->bi_disk;
		bio->bi_next = NULL;
		bio_set_dev(bio, rdev->bdev);
		if (test_bit(Faulty, &rdev->flags)) {
			bio_io_error(bio);
		} else if (unlikely((bio_op(bio) == REQ_OP_DISCARD) &&
				    !blk_queue_discard(bio->bi_disk->queue)))
			/* Just ignore it */
			bio_endio(bio);
		else
			generic_make_request(bio);
		bio = next;
	}
}