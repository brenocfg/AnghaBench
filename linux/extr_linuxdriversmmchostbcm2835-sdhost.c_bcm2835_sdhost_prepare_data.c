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
struct mmc_data {int blksz; int blocks; int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; scalar_t__ bytes_xfered; } ;
struct mmc_command {struct mmc_data* data; } ;
struct TYPE_6__ {int capacity; int read_blkbits; } ;
struct TYPE_5__ {int sectors; } ;
struct mmc_card {TYPE_3__ csd; TYPE_2__ ext_csd; } ;
struct bcm2835_host {int sectors; int blocks; struct mmc_data* data; int /*<<< orphan*/  sg_miter; int /*<<< orphan*/  dma_desc; TYPE_1__* mmc; scalar_t__ flush_fifo; scalar_t__ data_complete; } ;
struct TYPE_4__ {int max_blk_size; struct mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDHBCT ; 
 int /*<<< orphan*/  SDHBLC ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_data*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_set_transfer_irqs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_blockaddr (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_sd (struct mmc_card*) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm2835_sdhost_prepare_data(struct bcm2835_host *host, struct mmc_command *cmd)
{
	struct mmc_data *data = cmd->data;

	WARN_ON(host->data);

	host->data = data;
	if (!data)
		return;

	/* Sanity checks */
	BUG_ON(data->blksz * data->blocks > 524288);
	BUG_ON(data->blksz > host->mmc->max_blk_size);
	BUG_ON(data->blocks > 65535);

	host->data_complete = 0;
	host->flush_fifo = 0;
	host->data->bytes_xfered = 0;

	if (!host->sectors && host->mmc->card) {
		struct mmc_card *card = host->mmc->card;
		if (!mmc_card_sd(card) && mmc_card_blockaddr(card)) {
			/*
			 * The EXT_CSD sector count is in number of 512 byte
			 * sectors.
			 */
			host->sectors = card->ext_csd.sectors;
		} else {
			/*
			 * The CSD capacity field is in units of read_blkbits.
			 * set_capacity takes units of 512 bytes.
			 */
			host->sectors = card->csd.capacity <<
				(card->csd.read_blkbits - 9);
		}
	}

	if (!host->dma_desc) {
		/* Use PIO */
		int flags = SG_MITER_ATOMIC;

		if (data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		else
			flags |= SG_MITER_FROM_SG;
		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->blocks = data->blocks;
	}

	bcm2835_sdhost_set_transfer_irqs(host);

	bcm2835_sdhost_write(host, data->blksz, SDHBCT);
	bcm2835_sdhost_write(host, data->blocks, SDHBLC);

	BUG_ON(!host->data);
}