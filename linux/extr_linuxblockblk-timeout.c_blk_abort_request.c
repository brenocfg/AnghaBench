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
struct request {TYPE_1__* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout_work; scalar_t__ mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 scalar_t__ blk_mark_rq_complete (struct request*) ; 
 int /*<<< orphan*/  blk_rq_set_deadline (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_timed_out (struct request*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 

void blk_abort_request(struct request *req)
{
	if (req->q->mq_ops) {
		/*
		 * All we need to ensure is that timeout scan takes place
		 * immediately and that scan sees the new timeout value.
		 * No need for fancy synchronizations.
		 */
		blk_rq_set_deadline(req, jiffies);
		kblockd_schedule_work(&req->q->timeout_work);
	} else {
		if (blk_mark_rq_complete(req))
			return;
		blk_delete_timer(req);
		blk_rq_timed_out(req);
	}
}