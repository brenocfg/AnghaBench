#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int nr_phys_segments; TYPE_2__* biotail; TYPE_1__* bio; } ;
struct TYPE_5__ {unsigned int bi_seg_back_size; } ;
struct TYPE_4__ {unsigned int bi_seg_front_size; } ;

/* Variables and functions */
 int blk_integrity_merge_rq (struct request_queue*,struct request*,struct request*) ; 
 scalar_t__ blk_phys_contig_segment (struct request_queue*,TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ blk_rq_get_max_sectors (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int queue_max_segments (struct request_queue*) ; 
 scalar_t__ req_gap_back_merge (struct request*,TYPE_1__*) ; 
 scalar_t__ req_no_special_merge (struct request*) ; 

__attribute__((used)) static int ll_merge_requests_fn(struct request_queue *q, struct request *req,
				struct request *next)
{
	int total_phys_segments;
	unsigned int seg_size =
		req->biotail->bi_seg_back_size + next->bio->bi_seg_front_size;

	/*
	 * First check if the either of the requests are re-queued
	 * requests.  Can't merge them if they are.
	 */
	if (req_no_special_merge(req) || req_no_special_merge(next))
		return 0;

	if (req_gap_back_merge(req, next->bio))
		return 0;

	/*
	 * Will it become too large?
	 */
	if ((blk_rq_sectors(req) + blk_rq_sectors(next)) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		return 0;

	total_phys_segments = req->nr_phys_segments + next->nr_phys_segments;
	if (blk_phys_contig_segment(q, req->biotail, next->bio)) {
		if (req->nr_phys_segments == 1)
			req->bio->bi_seg_front_size = seg_size;
		if (next->nr_phys_segments == 1)
			next->biotail->bi_seg_back_size = seg_size;
		total_phys_segments--;
	}

	if (total_phys_segments > queue_max_segments(q))
		return 0;

	if (blk_integrity_merge_rq(q, req, next) == false)
		return 0;

	/* Merge is OK... */
	req->nr_phys_segments = total_phys_segments;
	return 1;
}