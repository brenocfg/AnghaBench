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
struct request {int /*<<< orphan*/  __data_len; struct bio* biotail; int /*<<< orphan*/  q; int /*<<< orphan*/  bio; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; struct bio* bi_next; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_bounce (int /*<<< orphan*/ ,struct bio**) ; 
 int /*<<< orphan*/  blk_rq_bio_prep (int /*<<< orphan*/ ,struct request*,struct bio*) ; 
 int /*<<< orphan*/  ll_back_merge_fn (int /*<<< orphan*/ ,struct request*,struct bio*) ; 

int blk_rq_append_bio(struct request *rq, struct bio **bio)
{
	struct bio *orig_bio = *bio;

	blk_queue_bounce(rq->q, bio);

	if (!rq->bio) {
		blk_rq_bio_prep(rq->q, rq, *bio);
	} else {
		if (!ll_back_merge_fn(rq->q, rq, *bio)) {
			if (orig_bio != *bio) {
				bio_put(*bio);
				*bio = orig_bio;
			}
			return -EINVAL;
		}

		rq->biotail->bi_next = *bio;
		rq->biotail = *bio;
		rq->__data_len += (*bio)->bi_iter.bi_size;
	}

	return 0;
}