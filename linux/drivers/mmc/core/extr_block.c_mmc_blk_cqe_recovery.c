#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmc_queue {int /*<<< orphan*/  blkdata; struct mmc_card* card; } ;
struct mmc_host {int dummy; } ;
struct mmc_card {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BLK_CQE_RECOVERY ; 
 int /*<<< orphan*/  mmc_blk_reset (int /*<<< orphan*/ ,struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_blk_reset_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_cqe_recovery (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void mmc_blk_cqe_recovery(struct mmc_queue *mq)
{
	struct mmc_card *card = mq->card;
	struct mmc_host *host = card->host;
	int err;

	pr_debug("%s: CQE recovery start\n", mmc_hostname(host));

	err = mmc_cqe_recovery(host);
	if (err)
		mmc_blk_reset(mq->blkdata, host, MMC_BLK_CQE_RECOVERY);
	else
		mmc_blk_reset_success(mq->blkdata, MMC_BLK_CQE_RECOVERY);

	pr_debug("%s: CQE recovery done\n", mmc_hostname(host));
}