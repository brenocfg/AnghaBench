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
struct mmc_queue {int /*<<< orphan*/  use_cqe; struct mmc_blk_data* blkdata; } ;
struct mmc_host {int dummy; } ;
struct mmc_card {struct mmc_host* host; } ;
struct TYPE_2__ {struct mmc_card* card; } ;
struct mmc_blk_data {int /*<<< orphan*/  part_type; TYPE_1__ queue; } ;
typedef  enum mmc_issued { ____Placeholder_mmc_issued } mmc_issued ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  MMC_ISSUE_ASYNC 137 
#define  MMC_ISSUE_DCMD 136 
#define  MMC_ISSUE_SYNC 135 
 int MMC_REQ_BUSY ; 
 int MMC_REQ_FAILED_TO_START ; 
 int MMC_REQ_FINISHED ; 
 int MMC_REQ_STARTED ; 
#define  REQ_OP_DISCARD 134 
#define  REQ_OP_DRV_IN 133 
#define  REQ_OP_DRV_OUT 132 
#define  REQ_OP_FLUSH 131 
#define  REQ_OP_READ 130 
#define  REQ_OP_SECURE_ERASE 129 
#define  REQ_OP_WRITE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int mmc_blk_cqe_issue_flush (struct mmc_queue*,struct request*) ; 
 int mmc_blk_cqe_issue_rw_rq (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_issue_discard_rq (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_issue_drv_op (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_issue_flush (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_issue_secdiscard_rq (struct mmc_queue*,struct request*) ; 
 int mmc_blk_mq_issue_rw_rq (struct mmc_queue*,struct request*) ; 
 int mmc_blk_part_switch (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int mmc_blk_wait_for_idle (struct mmc_queue*,struct mmc_host*) ; 
 int mmc_issue_type (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  req_op (struct request*) ; 

enum mmc_issued mmc_blk_mq_issue_rq(struct mmc_queue *mq, struct request *req)
{
	struct mmc_blk_data *md = mq->blkdata;
	struct mmc_card *card = md->queue.card;
	struct mmc_host *host = card->host;
	int ret;

	ret = mmc_blk_part_switch(card, md->part_type);
	if (ret)
		return MMC_REQ_FAILED_TO_START;

	switch (mmc_issue_type(mq, req)) {
	case MMC_ISSUE_SYNC:
		ret = mmc_blk_wait_for_idle(mq, host);
		if (ret)
			return MMC_REQ_BUSY;
		switch (req_op(req)) {
		case REQ_OP_DRV_IN:
		case REQ_OP_DRV_OUT:
			mmc_blk_issue_drv_op(mq, req);
			break;
		case REQ_OP_DISCARD:
			mmc_blk_issue_discard_rq(mq, req);
			break;
		case REQ_OP_SECURE_ERASE:
			mmc_blk_issue_secdiscard_rq(mq, req);
			break;
		case REQ_OP_FLUSH:
			mmc_blk_issue_flush(mq, req);
			break;
		default:
			WARN_ON_ONCE(1);
			return MMC_REQ_FAILED_TO_START;
		}
		return MMC_REQ_FINISHED;
	case MMC_ISSUE_DCMD:
	case MMC_ISSUE_ASYNC:
		switch (req_op(req)) {
		case REQ_OP_FLUSH:
			ret = mmc_blk_cqe_issue_flush(mq, req);
			break;
		case REQ_OP_READ:
		case REQ_OP_WRITE:
			if (mq->use_cqe)
				ret = mmc_blk_cqe_issue_rw_rq(mq, req);
			else
				ret = mmc_blk_mq_issue_rw_rq(mq, req);
			break;
		default:
			WARN_ON_ONCE(1);
			ret = -EINVAL;
		}
		if (!ret)
			return MMC_REQ_STARTED;
		return ret == -EBUSY ? MMC_REQ_BUSY : MMC_REQ_FAILED_TO_START;
	default:
		WARN_ON_ONCE(1);
		return MMC_REQ_FAILED_TO_START;
	}
}