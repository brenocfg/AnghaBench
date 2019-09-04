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
struct request {int dummy; } ;
struct mmc_request {int dummy; } ;
struct TYPE_3__ {struct mmc_request mrq; } ;
struct mmc_queue_req {TYPE_1__ brq; } ;
struct mmc_queue {scalar_t__ in_recovery; TYPE_2__* card; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 int /*<<< orphan*/  mmc_blk_mq_complete_rq (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_mq_dec_in_flight (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_post_req (struct mmc_host*,struct mmc_request*,int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static void mmc_blk_mq_post_req(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_request *mrq = &mqrq->brq.mrq;
	struct mmc_host *host = mq->card->host;

	mmc_post_req(host, mrq, 0);

	/*
	 * Block layer timeouts race with completions which means the normal
	 * completion path cannot be used during recovery.
	 */
	if (mq->in_recovery)
		mmc_blk_mq_complete_rq(mq, req);
	else
		blk_mq_complete_request(req);

	mmc_blk_mq_dec_in_flight(mq, req);
}