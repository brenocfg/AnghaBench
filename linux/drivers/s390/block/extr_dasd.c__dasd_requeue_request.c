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
struct request {int dummy; } ;
struct dasd_ccw_req {TYPE_1__* dq; scalar_t__ callback_data; struct dasd_block* block; } ;
struct dasd_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _dasd_requeue_request(struct dasd_ccw_req *cqr)
{
	struct dasd_block *block = cqr->block;
	struct request *req;

	if (!block)
		return -EINVAL;
	spin_lock_irq(&cqr->dq->lock);
	req = (struct request *) cqr->callback_data;
	blk_mq_requeue_request(req, false);
	spin_unlock_irq(&cqr->dq->lock);

	return 0;
}