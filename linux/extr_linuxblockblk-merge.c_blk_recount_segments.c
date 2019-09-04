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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct bio {unsigned short bi_vcnt; unsigned short bi_phys_segments; struct bio* bi_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  BIO_SEG_VALID ; 
 int /*<<< orphan*/  QUEUE_FLAG_NO_SG_MERGE ; 
 unsigned short __blk_recalc_rq_segments (struct request_queue*,struct bio*,int) ; 
 scalar_t__ bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 unsigned short bio_segments (struct bio*) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 unsigned short queue_max_segments (struct request_queue*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_recount_segments(struct request_queue *q, struct bio *bio)
{
	unsigned short seg_cnt;

	/* estimate segment number by bi_vcnt for non-cloned bio */
	if (bio_flagged(bio, BIO_CLONED))
		seg_cnt = bio_segments(bio);
	else
		seg_cnt = bio->bi_vcnt;

	if (test_bit(QUEUE_FLAG_NO_SG_MERGE, &q->queue_flags) &&
			(seg_cnt < queue_max_segments(q)))
		bio->bi_phys_segments = seg_cnt;
	else {
		struct bio *nxt = bio->bi_next;

		bio->bi_next = NULL;
		bio->bi_phys_segments = __blk_recalc_rq_segments(q, bio, false);
		bio->bi_next = nxt;
	}

	bio_set_flag(bio, BIO_SEG_VALID);
}