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
struct request {int /*<<< orphan*/  q; } ;
struct deadline_data {struct request** next_rq; } ;

/* Variables and functions */
 int READ ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WRITE ; 
 int /*<<< orphan*/  blk_queue_is_zoned (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_req_can_dispatch_to_zone (struct request*) ; 
 struct request* deadline_latter_request (struct request*) ; 

__attribute__((used)) static struct request *
deadline_next_request(struct deadline_data *dd, int data_dir)
{
	struct request *rq;

	if (WARN_ON_ONCE(data_dir != READ && data_dir != WRITE))
		return NULL;

	rq = dd->next_rq[data_dir];
	if (!rq)
		return NULL;

	if (data_dir == READ || !blk_queue_is_zoned(rq->q))
		return rq;

	/*
	 * Look for a write request that can be dispatched, that is one with
	 * an unlocked target zone.
	 */
	while (rq) {
		if (blk_req_can_dispatch_to_zone(rq))
			return rq;
		rq = deadline_latter_request(rq);
	}

	return NULL;
}