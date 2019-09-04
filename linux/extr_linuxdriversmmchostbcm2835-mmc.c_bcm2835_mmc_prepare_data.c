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
typedef  int /*<<< orphan*/  u8 ;
struct mmc_data {int blksz; int blocks; int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; scalar_t__ bytes_xfered; } ;
struct mmc_command {int flags; struct mmc_data* data; } ;
struct bcm2835_host {int flags; int blocks; int use_dma; struct mmc_data* data; scalar_t__ have_dma; int /*<<< orphan*/  sg_miter; scalar_t__ data_early; TYPE_1__* mmc; } ;
struct TYPE_2__ {int max_blk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_BUSY ; 
 int PIO_DMA_BARRIER ; 
 int /*<<< orphan*/  SDHCI_BLOCK_COUNT ; 
 int /*<<< orphan*/  SDHCI_BLOCK_SIZE ; 
 int /*<<< orphan*/  SDHCI_DEFAULT_BOUNDARY_ARG ; 
 int SDHCI_MAKE_BLKSZ (int /*<<< orphan*/ ,int) ; 
 int SDHCI_REQ_USE_DMA ; 
 int /*<<< orphan*/  SDHCI_TIMEOUT_CONTROL ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  TIMEOUT_VAL ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_data*) ; 
 int /*<<< orphan*/  bcm2835_mmc_set_transfer_irqs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_mmc_writeb (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writew (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm2835_mmc_prepare_data(struct bcm2835_host *host, struct mmc_command *cmd)
{
	u8 count;
	struct mmc_data *data = cmd->data;

	WARN_ON(host->data);

	if (data || (cmd->flags & MMC_RSP_BUSY)) {
		count = TIMEOUT_VAL;
		bcm2835_mmc_writeb(host, count, SDHCI_TIMEOUT_CONTROL);
	}

	if (!data)
		return;

	/* Sanity checks */
	BUG_ON(data->blksz * data->blocks > 524288);
	BUG_ON(data->blksz > host->mmc->max_blk_size);
	BUG_ON(data->blocks > 65535);

	host->data = data;
	host->data_early = 0;
	host->data->bytes_xfered = 0;


	if (!(host->flags & SDHCI_REQ_USE_DMA)) {
		int flags;

		flags = SG_MITER_ATOMIC;
		if (host->data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		else
			flags |= SG_MITER_FROM_SG;
		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->blocks = data->blocks;
	}

	host->use_dma = host->have_dma && data->blocks > PIO_DMA_BARRIER;

	bcm2835_mmc_set_transfer_irqs(host);

	/* Set the DMA boundary value and block size */
	bcm2835_mmc_writew(host, SDHCI_MAKE_BLKSZ(SDHCI_DEFAULT_BOUNDARY_ARG,
		data->blksz), SDHCI_BLOCK_SIZE);
	bcm2835_mmc_writew(host, data->blocks, SDHCI_BLOCK_COUNT);

	BUG_ON(!host->data);
}