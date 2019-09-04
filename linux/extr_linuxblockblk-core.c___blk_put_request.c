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
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;
struct request_list {int dummy; } ;
struct request {int rq_flags; int /*<<< orphan*/  queuelist; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/ * bio; } ;
typedef  int req_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ELV_ON_HASH (struct request*) ; 
 int RQF_ALLOCED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_free_request (struct request_list*,struct request*) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  blk_pm_put_request (struct request*) ; 
 int /*<<< orphan*/  blk_put_rl (struct request_list*) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 
 int /*<<< orphan*/  blk_req_zone_write_unlock (struct request*) ; 
 struct request_list* blk_rq_rl (struct request*) ; 
 int /*<<< orphan*/  elv_completed_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  freed_request (struct request_list*,int,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int op_is_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_done (struct request_queue*,struct request*) ; 
 scalar_t__ unlikely (int) ; 

void __blk_put_request(struct request_queue *q, struct request *req)
{
	req_flags_t rq_flags = req->rq_flags;

	if (unlikely(!q))
		return;

	if (q->mq_ops) {
		blk_mq_free_request(req);
		return;
	}

	lockdep_assert_held(q->queue_lock);

	blk_req_zone_write_unlock(req);
	blk_pm_put_request(req);

	elv_completed_request(q, req);

	/* this is a bio leak */
	WARN_ON(req->bio != NULL);

	rq_qos_done(q, req);

	/*
	 * Request may not have originated from ll_rw_blk. if not,
	 * it didn't come out of our reserved rq pools
	 */
	if (rq_flags & RQF_ALLOCED) {
		struct request_list *rl = blk_rq_rl(req);
		bool sync = op_is_sync(req->cmd_flags);

		BUG_ON(!list_empty(&req->queuelist));
		BUG_ON(ELV_ON_HASH(req));

		blk_free_request(rl, req);
		freed_request(rl, sync, rq_flags);
		blk_put_rl(rl);
		blk_queue_exit(q);
	}
}