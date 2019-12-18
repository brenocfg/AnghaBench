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
struct request {TYPE_1__* rq_disk; } ;
struct TYPE_8__ {int bytes_xfered; int blocks; } ;
struct TYPE_7__ {scalar_t__ error; } ;
struct TYPE_6__ {scalar_t__ error; } ;
struct mmc_blk_request {TYPE_4__ data; TYPE_3__ cmd; TYPE_2__ sbc; } ;
struct mmc_queue_req {scalar_t__ retries; struct mmc_blk_request brq; } ;
struct mmc_queue {struct mmc_card* card; struct mmc_blk_data* blkdata; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;
struct mmc_blk_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int MMC_BLK_READ ; 
 int MMC_BLK_WRITE ; 
 scalar_t__ MMC_DATA_RETRIES ; 
 scalar_t__ MMC_MAX_RETRIES ; 
 scalar_t__ MMC_NO_RETRIES ; 
 scalar_t__ READ ; 
 scalar_t__ WRITE ; 
 int __mmc_send_status (struct mmc_card*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_blk_cmd_started (struct mmc_blk_request*) ; 
 int mmc_blk_fix_state (struct mmc_card*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_in_tran_state (int) ; 
 int /*<<< orphan*/  mmc_blk_read_single (struct mmc_queue*,struct request*) ; 
 scalar_t__ mmc_blk_reset (struct mmc_blk_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmc_blk_status_error (struct request*,int) ; 
 scalar_t__ mmc_card_sd (struct mmc_card*) ; 
 scalar_t__ mmc_detect_card_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_large_sector (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_retune_release (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_sd_num_wr_blocks (struct mmc_card*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void mmc_blk_mq_rw_recovery(struct mmc_queue *mq, struct request *req)
{
	int type = rq_data_dir(req) == READ ? MMC_BLK_READ : MMC_BLK_WRITE;
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_blk_request *brq = &mqrq->brq;
	struct mmc_blk_data *md = mq->blkdata;
	struct mmc_card *card = mq->card;
	u32 status;
	u32 blocks;
	int err;

	/*
	 * Some errors the host driver might not have seen. Set the number of
	 * bytes transferred to zero in that case.
	 */
	err = __mmc_send_status(card, &status, 0);
	if (err || mmc_blk_status_error(req, status))
		brq->data.bytes_xfered = 0;

	mmc_retune_release(card->host);

	/*
	 * Try again to get the status. This also provides an opportunity for
	 * re-tuning.
	 */
	if (err)
		err = __mmc_send_status(card, &status, 0);

	/*
	 * Nothing more to do after the number of bytes transferred has been
	 * updated and there is no card.
	 */
	if (err && mmc_detect_card_removed(card->host))
		return;

	/* Try to get back to "tran" state */
	if (!mmc_host_is_spi(mq->card->host) &&
	    (err || !mmc_blk_in_tran_state(status)))
		err = mmc_blk_fix_state(mq->card, req);

	/*
	 * Special case for SD cards where the card might record the number of
	 * blocks written.
	 */
	if (!err && mmc_blk_cmd_started(brq) && mmc_card_sd(card) &&
	    rq_data_dir(req) == WRITE) {
		if (mmc_sd_num_wr_blocks(card, &blocks))
			brq->data.bytes_xfered = 0;
		else
			brq->data.bytes_xfered = blocks << 9;
	}

	/* Reset if the card is in a bad state */
	if (!mmc_host_is_spi(mq->card->host) &&
	    err && mmc_blk_reset(md, card->host, type)) {
		pr_err("%s: recovery failed!\n", req->rq_disk->disk_name);
		mqrq->retries = MMC_NO_RETRIES;
		return;
	}

	/*
	 * If anything was done, just return and if there is anything remaining
	 * on the request it will get requeued.
	 */
	if (brq->data.bytes_xfered)
		return;

	/* Reset before last retry */
	if (mqrq->retries + 1 == MMC_MAX_RETRIES)
		mmc_blk_reset(md, card->host, type);

	/* Command errors fail fast, so use all MMC_MAX_RETRIES */
	if (brq->sbc.error || brq->cmd.error)
		return;

	/* Reduce the remaining retries for data errors */
	if (mqrq->retries < MMC_MAX_RETRIES - MMC_DATA_RETRIES) {
		mqrq->retries = MMC_MAX_RETRIES - MMC_DATA_RETRIES;
		return;
	}

	/* FIXME: Missing single sector read for large sector size */
	if (!mmc_large_sector(card) && rq_data_dir(req) == READ &&
	    brq->data.blocks > 1) {
		/* Read one sector at a time */
		mmc_blk_read_single(mq, req);
		return;
	}
}