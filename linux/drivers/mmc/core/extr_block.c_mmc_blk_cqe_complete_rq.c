#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {struct request_queue* q; } ;
struct mmc_request {TYPE_3__* data; TYPE_2__* cmd; } ;
struct TYPE_5__ {struct mmc_request mrq; } ;
struct mmc_queue_req {int /*<<< orphan*/  retries; TYPE_1__ brq; } ;
struct mmc_queue {int* in_flight; int /*<<< orphan*/  ctx; TYPE_4__* card; int /*<<< orphan*/  cqe_busy; int /*<<< orphan*/  lock; } ;
struct mmc_host {int dummy; } ;
struct TYPE_8__ {struct mmc_host* host; } ;
struct TYPE_7__ {int error; int /*<<< orphan*/  bytes_xfered; } ;
struct TYPE_6__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ MMC_CQE_RETRIES ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_cqe_check_busy (struct mmc_queue*) ; 
 int /*<<< orphan*/  mmc_cqe_post_req (struct mmc_host*,struct mmc_request*) ; 
 size_t mmc_issue_type (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_put_card (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mmc_tot_in_flight (struct mmc_queue*) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mmc_blk_cqe_complete_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_request *mrq = &mqrq->brq.mrq;
	struct request_queue *q = req->q;
	struct mmc_host *host = mq->card->host;
	unsigned long flags;
	bool put_card;
	int err;

	mmc_cqe_post_req(host, mrq);

	if (mrq->cmd && mrq->cmd->error)
		err = mrq->cmd->error;
	else if (mrq->data && mrq->data->error)
		err = mrq->data->error;
	else
		err = 0;

	if (err) {
		if (mqrq->retries++ < MMC_CQE_RETRIES)
			blk_mq_requeue_request(req, true);
		else
			blk_mq_end_request(req, BLK_STS_IOERR);
	} else if (mrq->data) {
		if (blk_update_request(req, BLK_STS_OK, mrq->data->bytes_xfered))
			blk_mq_requeue_request(req, true);
		else
			__blk_mq_end_request(req, BLK_STS_OK);
	} else {
		blk_mq_end_request(req, BLK_STS_OK);
	}

	spin_lock_irqsave(&mq->lock, flags);

	mq->in_flight[mmc_issue_type(mq, req)] -= 1;

	put_card = (mmc_tot_in_flight(mq) == 0);

	mmc_cqe_check_busy(mq);

	spin_unlock_irqrestore(&mq->lock, flags);

	if (!mq->cqe_busy)
		blk_mq_run_hw_queues(q, true);

	if (put_card)
		mmc_put_card(mq->card, &mq->ctx);
}