#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  done; } ;
struct TYPE_6__ {TYPE_2__ mrq; } ;
struct mmc_queue_req {TYPE_1__ brq; } ;
struct mmc_queue {int rw_wait; TYPE_5__* card; } ;
struct mmc_host {int dummy; } ;
struct TYPE_8__ {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_blk_mq_post_req (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_mq_req_done ; 
 int /*<<< orphan*/  mmc_blk_rw_rq_prep (struct mmc_queue_req*,TYPE_5__*,int /*<<< orphan*/ ,struct mmc_queue*) ; 
 int mmc_blk_rw_wait (struct mmc_queue*,struct request**) ; 
 scalar_t__ mmc_host_done_complete (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_post_req (struct mmc_host*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mmc_pre_req (struct mmc_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_retune_release (struct mmc_host*) ; 
 int mmc_start_request (struct mmc_host*,TYPE_2__*) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static int mmc_blk_mq_issue_rw_rq(struct mmc_queue *mq,
				  struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_host *host = mq->card->host;
	struct request *prev_req = NULL;
	int err = 0;

	mmc_blk_rw_rq_prep(mqrq, mq->card, 0, mq);

	mqrq->brq.mrq.done = mmc_blk_mq_req_done;

	mmc_pre_req(host, &mqrq->brq.mrq);

	err = mmc_blk_rw_wait(mq, &prev_req);
	if (err)
		goto out_post_req;

	mq->rw_wait = true;

	err = mmc_start_request(host, &mqrq->brq.mrq);

	if (prev_req)
		mmc_blk_mq_post_req(mq, prev_req);

	if (err)
		mq->rw_wait = false;

	/* Release re-tuning here where there is no synchronization required */
	if (err || mmc_host_done_complete(host))
		mmc_retune_release(host);

out_post_req:
	if (err)
		mmc_post_req(host, &mqrq->brq.mrq, err);

	return err;
}