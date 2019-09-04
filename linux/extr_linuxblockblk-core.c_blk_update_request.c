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
struct request {int rq_flags; int __sector; int cmd_flags; scalar_t__ __data_len; struct bio* bio; } ;
struct TYPE_2__ {unsigned int bi_size; } ;
struct bio {int bi_opf; struct bio* bi_next; TYPE_1__ bi_iter; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TRACE_COMPLETION ; 
 int REQ_FAILFAST_MASK ; 
 int RQF_MIXED_MERGE ; 
 int RQF_QUIET ; 
 int RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  bio_clear_flag (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_account_io_completion (struct request*,unsigned int) ; 
 int /*<<< orphan*/  blk_dump_rq_flags (struct request*,char*) ; 
 int /*<<< orphan*/  blk_recalc_rq_segments (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_cur_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  blk_status_to_errno (scalar_t__) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  print_req_error (struct request*,scalar_t__) ; 
 int /*<<< orphan*/  req_bio_endio (struct request*,struct bio*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  trace_block_rq_complete (struct request*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

bool blk_update_request(struct request *req, blk_status_t error,
		unsigned int nr_bytes)
{
	int total_bytes;

	trace_block_rq_complete(req, blk_status_to_errno(error), nr_bytes);

	if (!req->bio)
		return false;

	if (unlikely(error && !blk_rq_is_passthrough(req) &&
		     !(req->rq_flags & RQF_QUIET)))
		print_req_error(req, error);

	blk_account_io_completion(req, nr_bytes);

	total_bytes = 0;
	while (req->bio) {
		struct bio *bio = req->bio;
		unsigned bio_bytes = min(bio->bi_iter.bi_size, nr_bytes);

		if (bio_bytes == bio->bi_iter.bi_size)
			req->bio = bio->bi_next;

		/* Completion has already been traced */
		bio_clear_flag(bio, BIO_TRACE_COMPLETION);
		req_bio_endio(req, bio, bio_bytes, error);

		total_bytes += bio_bytes;
		nr_bytes -= bio_bytes;

		if (!nr_bytes)
			break;
	}

	/*
	 * completely done
	 */
	if (!req->bio) {
		/*
		 * Reset counters so that the request stacking driver
		 * can find how many bytes remain in the request
		 * later.
		 */
		req->__data_len = 0;
		return false;
	}

	req->__data_len -= total_bytes;

	/* update sector only for requests with clear definition of sector */
	if (!blk_rq_is_passthrough(req))
		req->__sector += total_bytes >> 9;

	/* mixed attributes always follow the first bio */
	if (req->rq_flags & RQF_MIXED_MERGE) {
		req->cmd_flags &= ~REQ_FAILFAST_MASK;
		req->cmd_flags |= req->bio->bi_opf & REQ_FAILFAST_MASK;
	}

	if (!(req->rq_flags & RQF_SPECIAL_PAYLOAD)) {
		/*
		 * If total number of sectors is less than the first segment
		 * size, something has gone terribly wrong.
		 */
		if (blk_rq_bytes(req) < blk_rq_cur_bytes(req)) {
			blk_dump_rq_flags(req, "request botched");
			req->__data_len = blk_rq_cur_bytes(req);
		}

		/* recalculate the number of segments */
		blk_recalc_rq_segments(req);
	}

	return true;
}