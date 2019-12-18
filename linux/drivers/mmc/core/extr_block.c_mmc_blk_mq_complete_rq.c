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
struct request {int /*<<< orphan*/  rq_flags; } ;
struct TYPE_3__ {unsigned int bytes_xfered; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct mmc_queue_req {int /*<<< orphan*/  retries; TYPE_2__ brq; } ;
struct mmc_queue {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ MMC_MAX_RETRIES ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mmc_card_removed (int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static void mmc_blk_mq_complete_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	unsigned int nr_bytes = mqrq->brq.data.bytes_xfered;

	if (nr_bytes) {
		if (blk_update_request(req, BLK_STS_OK, nr_bytes))
			blk_mq_requeue_request(req, true);
		else
			__blk_mq_end_request(req, BLK_STS_OK);
	} else if (!blk_rq_bytes(req)) {
		__blk_mq_end_request(req, BLK_STS_IOERR);
	} else if (mqrq->retries++ < MMC_MAX_RETRIES) {
		blk_mq_requeue_request(req, true);
	} else {
		if (mmc_card_removed(mq->card))
			req->rq_flags |= RQF_QUIET;
		blk_mq_end_request(req, BLK_STS_IOERR);
	}
}