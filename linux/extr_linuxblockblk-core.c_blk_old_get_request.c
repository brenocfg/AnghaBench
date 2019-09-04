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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  node; int /*<<< orphan*/  mq_ops; } ;
struct request {int /*<<< orphan*/ * biotail; int /*<<< orphan*/  bio; scalar_t__ __sector; scalar_t__ __data_len; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int blk_mq_req_flags_t ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 struct request* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int blk_queue_enter (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 
 int /*<<< orphan*/  create_io_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct request* get_request (struct request_queue*,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *blk_old_get_request(struct request_queue *q,
				unsigned int op, blk_mq_req_flags_t flags)
{
	struct request *rq;
	gfp_t gfp_mask = flags & BLK_MQ_REQ_NOWAIT ? GFP_ATOMIC : GFP_NOIO;
	int ret = 0;

	WARN_ON_ONCE(q->mq_ops);

	/* create ioc upfront */
	create_io_context(gfp_mask, q->node);

	ret = blk_queue_enter(q, flags);
	if (ret)
		return ERR_PTR(ret);
	spin_lock_irq(q->queue_lock);
	rq = get_request(q, op, NULL, flags, gfp_mask);
	if (IS_ERR(rq)) {
		spin_unlock_irq(q->queue_lock);
		blk_queue_exit(q);
		return rq;
	}

	/* q->queue_lock is unlocked at this point */
	rq->__data_len = 0;
	rq->__sector = (sector_t) -1;
	rq->bio = rq->biotail = NULL;
	return rq;
}