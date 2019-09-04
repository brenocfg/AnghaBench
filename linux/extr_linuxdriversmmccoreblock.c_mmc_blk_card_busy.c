#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct request {int dummy; } ;
struct TYPE_5__ {int* resp; } ;
struct TYPE_4__ {scalar_t__ bytes_xfered; } ;
struct TYPE_6__ {TYPE_2__ cmd; TYPE_1__ data; } ;
struct mmc_queue_req {TYPE_3__ brq; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MMC_BLK_TIMEOUT_MS ; 
 int R1_EXCEPTION_EVENT ; 
 scalar_t__ READ ; 
 int card_busy_detect (struct mmc_card*,int /*<<< orphan*/ ,struct request*,int*) ; 
 int mmc_blk_stop_err_bits (TYPE_3__*) ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 scalar_t__ mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static int mmc_blk_card_busy(struct mmc_card *card, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	u32 status = 0;
	int err;

	if (mmc_host_is_spi(card->host) || rq_data_dir(req) == READ)
		return 0;

	err = card_busy_detect(card, MMC_BLK_TIMEOUT_MS, req, &status);

	/*
	 * Do not assume data transferred correctly if there are any error bits
	 * set.
	 */
	if (status & mmc_blk_stop_err_bits(&mqrq->brq)) {
		mqrq->brq.data.bytes_xfered = 0;
		err = err ? err : -EIO;
	}

	/* Copy the exception bit so it will be seen later on */
	if (mmc_card_mmc(card) && status & R1_EXCEPTION_EVENT)
		mqrq->brq.cmd.resp[0] |= R1_EXCEPTION_EVENT;

	return err;
}