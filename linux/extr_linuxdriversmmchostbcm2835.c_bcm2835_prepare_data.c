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
struct mmc_data {int flags; int /*<<< orphan*/  blocks; int /*<<< orphan*/  blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; scalar_t__ bytes_xfered; } ;
struct mmc_command {struct mmc_data* data; } ;
struct bcm2835_host {int data_complete; scalar_t__ ioaddr; int /*<<< orphan*/  blocks; int /*<<< orphan*/  sg_miter; int /*<<< orphan*/  dma_desc; struct mmc_data* data; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 scalar_t__ SDHBCT ; 
 scalar_t__ SDHBLC ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_data*) ; 
 int /*<<< orphan*/  bcm2835_set_transfer_irqs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static
void bcm2835_prepare_data(struct bcm2835_host *host, struct mmc_command *cmd)
{
	struct mmc_data *data = cmd->data;

	WARN_ON(host->data);

	host->data = data;
	if (!data)
		return;

	host->data_complete = false;
	host->data->bytes_xfered = 0;

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

	bcm2835_set_transfer_irqs(host);

	writel(data->blksz, host->ioaddr + SDHBCT);
	writel(data->blocks, host->ioaddr + SDHBLC);
}