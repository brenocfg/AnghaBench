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
struct request_queue {int dummy; } ;
struct request {int nr_phys_segments; scalar_t__ rq_disk; struct bio* biotail; struct bio* bio; int /*<<< orphan*/  __data_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {scalar_t__ bi_disk; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ bio_has_data (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int bio_phys_segments (struct request_queue*,struct bio*) ; 

void blk_rq_bio_prep(struct request_queue *q, struct request *rq,
		     struct bio *bio)
{
	if (bio_has_data(bio))
		rq->nr_phys_segments = bio_phys_segments(q, bio);
	else if (bio_op(bio) == REQ_OP_DISCARD)
		rq->nr_phys_segments = 1;

	rq->__data_len = bio->bi_iter.bi_size;
	rq->bio = rq->biotail = bio;

	if (bio->bi_disk)
		rq->rq_disk = bio->bi_disk;
}