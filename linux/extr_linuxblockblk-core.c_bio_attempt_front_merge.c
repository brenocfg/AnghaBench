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
struct request {int const cmd_flags; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  __data_len; int /*<<< orphan*/  __sector; struct bio* bio; } ;
struct TYPE_2__ {scalar_t__ bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {int const bi_opf; TYPE_1__ bi_iter; struct bio* bi_next; } ;

/* Variables and functions */
 int const REQ_FAILFAST_MASK ; 
 int /*<<< orphan*/  bio_prio (struct bio*) ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 int /*<<< orphan*/  blk_rq_set_mixed_merge (struct request*) ; 
 int /*<<< orphan*/  ioprio_best (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_front_merge_fn (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  trace_block_bio_frontmerge (struct request_queue*,struct request*,struct bio*) ; 

bool bio_attempt_front_merge(struct request_queue *q, struct request *req,
			     struct bio *bio)
{
	const int ff = bio->bi_opf & REQ_FAILFAST_MASK;

	if (!ll_front_merge_fn(q, req, bio))
		return false;

	trace_block_bio_frontmerge(q, req, bio);

	if ((req->cmd_flags & REQ_FAILFAST_MASK) != ff)
		blk_rq_set_mixed_merge(req);

	bio->bi_next = req->bio;
	req->bio = bio;

	req->__sector = bio->bi_iter.bi_sector;
	req->__data_len += bio->bi_iter.bi_size;
	req->ioprio = ioprio_best(req->ioprio, bio_prio(bio));

	blk_account_io_start(req, false);
	return true;
}