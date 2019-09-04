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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  mq_ops; } ;
struct request {struct request_queue* q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_finish_request (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_update_bidi_request (struct request*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool blk_end_bidi_request(struct request *rq, blk_status_t error,
				 unsigned int nr_bytes, unsigned int bidi_bytes)
{
	struct request_queue *q = rq->q;
	unsigned long flags;

	WARN_ON_ONCE(q->mq_ops);

	if (blk_update_bidi_request(rq, error, nr_bytes, bidi_bytes))
		return true;

	spin_lock_irqsave(q->queue_lock, flags);
	blk_finish_request(rq, error);
	spin_unlock_irqrestore(q->queue_lock, flags);

	return false;
}