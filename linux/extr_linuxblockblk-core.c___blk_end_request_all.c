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
struct request {struct request* next_rq; TYPE_1__* q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int __blk_end_bidi_request (struct request*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  blk_bidi_rq (struct request*) ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __blk_end_request_all(struct request *rq, blk_status_t error)
{
	bool pending;
	unsigned int bidi_bytes = 0;

	lockdep_assert_held(rq->q->queue_lock);
	WARN_ON_ONCE(rq->q->mq_ops);

	if (unlikely(blk_bidi_rq(rq)))
		bidi_bytes = blk_rq_bytes(rq->next_rq);

	pending = __blk_end_bidi_request(rq, error, blk_rq_bytes(rq), bidi_bytes);
	BUG_ON(pending);
}