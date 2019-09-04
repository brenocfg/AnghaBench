#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_2__* q; int /*<<< orphan*/  rq_flags; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_4__ {TYPE_1__* mq_ops; } ;
struct TYPE_3__ {int (* timeout ) (struct request*,int) ;} ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int BLK_EH_RESET_TIMER ; 
 int /*<<< orphan*/  RQF_TIMED_OUT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_add_timer (struct request*) ; 
 int stub1 (struct request*,int) ; 

__attribute__((used)) static void blk_mq_rq_timed_out(struct request *req, bool reserved)
{
	req->rq_flags |= RQF_TIMED_OUT;
	if (req->q->mq_ops->timeout) {
		enum blk_eh_timer_return ret;

		ret = req->q->mq_ops->timeout(req, reserved);
		if (ret == BLK_EH_DONE)
			return;
		WARN_ON_ONCE(ret != BLK_EH_RESET_TIMER);
	}

	blk_add_timer(req);
}