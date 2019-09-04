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
struct request_queue {struct request* last_merge; } ;
struct request {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_attempt_req_merge (struct request_queue*,struct request*,struct request*) ; 
 scalar_t__ blk_queue_nomerges (struct request_queue*) ; 
 scalar_t__ blk_queue_noxmerges (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 struct request* elv_rqhash_find (struct request_queue*,int /*<<< orphan*/ ) ; 

bool elv_attempt_insert_merge(struct request_queue *q, struct request *rq)
{
	struct request *__rq;
	bool ret;

	if (blk_queue_nomerges(q))
		return false;

	/*
	 * First try one-hit cache.
	 */
	if (q->last_merge && blk_attempt_req_merge(q, q->last_merge, rq))
		return true;

	if (blk_queue_noxmerges(q))
		return false;

	ret = false;
	/*
	 * See if our hash lookup can find a potential backmerge.
	 */
	while (1) {
		__rq = elv_rqhash_find(q, blk_rq_pos(rq));
		if (!__rq || !blk_attempt_req_merge(q, __rq, rq))
			break;

		/* The merged request could be merged with others, try again */
		ret = true;
		rq = __rq;
	}

	return ret;
}