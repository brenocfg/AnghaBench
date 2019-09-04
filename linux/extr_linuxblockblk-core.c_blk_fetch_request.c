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
struct request_queue {int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 

struct request *blk_fetch_request(struct request_queue *q)
{
	struct request *rq;

	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	rq = blk_peek_request(q);
	if (rq)
		blk_start_request(rq);
	return rq;
}