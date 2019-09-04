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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  mq_ops; } ;
struct request_list {int /*<<< orphan*/ * wait; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int blk_mq_req_flags_t ;
struct TYPE_2__ {int /*<<< orphan*/  io_context; } ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 struct request* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct request*) ; 
 unsigned int REQ_NOWAIT ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct request* __get_request (struct request_list*,unsigned int,struct bio*,int,int /*<<< orphan*/ ) ; 
 struct request_list* blk_get_rl (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  blk_put_rl (struct request_list*) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  ioc_set_batching (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int op_is_sync (unsigned int) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_block_sleeprq (struct request_queue*,struct bio*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct request *get_request(struct request_queue *q, unsigned int op,
		struct bio *bio, blk_mq_req_flags_t flags, gfp_t gfp)
{
	const bool is_sync = op_is_sync(op);
	DEFINE_WAIT(wait);
	struct request_list *rl;
	struct request *rq;

	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	rl = blk_get_rl(q, bio);	/* transferred to @rq on success */
retry:
	rq = __get_request(rl, op, bio, flags, gfp);
	if (!IS_ERR(rq))
		return rq;

	if (op & REQ_NOWAIT) {
		blk_put_rl(rl);
		return ERR_PTR(-EAGAIN);
	}

	if ((flags & BLK_MQ_REQ_NOWAIT) || unlikely(blk_queue_dying(q))) {
		blk_put_rl(rl);
		return rq;
	}

	/* wait on @rl and retry */
	prepare_to_wait_exclusive(&rl->wait[is_sync], &wait,
				  TASK_UNINTERRUPTIBLE);

	trace_block_sleeprq(q, bio, op);

	spin_unlock_irq(q->queue_lock);
	io_schedule();

	/*
	 * After sleeping, we become a "batching" process and will be able
	 * to allocate at least one request, and up to a big batch of them
	 * for a small period time.  See ioc_batching, ioc_set_batching
	 */
	ioc_set_batching(q, current->io_context);

	spin_lock_irq(q->queue_lock);
	finish_wait(&rl->wait[is_sync], &wait);

	goto retry;
}