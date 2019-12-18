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
struct mmc_queue {scalar_t__ use_cqe; } ;
struct TYPE_2__ {struct mmc_queue* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_blk_cqe_complete_rq (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_mq_complete_rq (struct mmc_queue*,struct request*) ; 

void mmc_blk_mq_complete(struct request *req)
{
	struct mmc_queue *mq = req->q->queuedata;

	if (mq->use_cqe)
		mmc_blk_cqe_complete_rq(mq, req);
	else
		mmc_blk_mq_complete_rq(mq, req);
}