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
struct request_queue {int dummy; } ;
struct request {unsigned short nr_phys_segments; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 scalar_t__ bio_sectors (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_rq_get_max_sectors (struct request*,int /*<<< orphan*/ ) ; 
 unsigned short blk_rq_nr_discard_segments (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 unsigned short queue_max_discard_segments (struct request_queue*) ; 
 int /*<<< orphan*/  req_set_nomerge (struct request_queue*,struct request*) ; 

__attribute__((used)) static bool req_attempt_discard_merge(struct request_queue *q, struct request *req,
		struct request *next)
{
	unsigned short segments = blk_rq_nr_discard_segments(req);

	if (segments >= queue_max_discard_segments(q))
		goto no_merge;
	if (blk_rq_sectors(req) + bio_sectors(next->bio) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		goto no_merge;

	req->nr_phys_segments = segments + blk_rq_nr_discard_segments(next);
	return true;
no_merge:
	req_set_nomerge(q, req);
	return false;
}