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
struct TYPE_4__ {int /*<<< orphan*/  mrq; } ;
struct mmc_queue_req {TYPE_2__ brq; } ;
struct mmc_queue {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int mmc_blk_cqe_start_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_blk_data_prep (struct mmc_queue*,struct mmc_queue_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static int mmc_blk_cqe_issue_rw_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);

	mmc_blk_data_prep(mq, mqrq, 0, NULL, NULL);

	return mmc_blk_cqe_start_req(mq->card->host, &mqrq->brq.mrq);
}