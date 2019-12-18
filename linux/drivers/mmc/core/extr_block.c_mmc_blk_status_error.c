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
typedef  int u32 ;
struct request {TYPE_4__* q; } ;
struct TYPE_7__ {int* resp; } ;
struct TYPE_6__ {int* resp; } ;
struct mmc_blk_request {TYPE_3__ stop; TYPE_2__ cmd; } ;
struct mmc_queue_req {struct mmc_blk_request brq; } ;
struct mmc_queue {TYPE_1__* card; } ;
struct TYPE_8__ {struct mmc_queue* queuedata; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int CMD_ERRORS ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  mmc_blk_in_tran_state (int) ; 
 int mmc_blk_stop_err_bits (struct mmc_blk_request*) ; 
 scalar_t__ mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static bool mmc_blk_status_error(struct request *req, u32 status)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_blk_request *brq = &mqrq->brq;
	struct mmc_queue *mq = req->q->queuedata;
	u32 stop_err_bits;

	if (mmc_host_is_spi(mq->card->host))
		return false;

	stop_err_bits = mmc_blk_stop_err_bits(brq);

	return brq->cmd.resp[0]  & CMD_ERRORS    ||
	       brq->stop.resp[0] & stop_err_bits ||
	       status            & stop_err_bits ||
	       (rq_data_dir(req) == WRITE && !mmc_blk_in_tran_state(status));
}