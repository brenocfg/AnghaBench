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
typedef  int u32 ;
struct bcm2835_host {scalar_t__ blocks; TYPE_1__* data; int /*<<< orphan*/  dma_desc; scalar_t__ debug; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_WRITE ; 
 int SDHSTS_CRC16_ERROR ; 
 int SDHSTS_FIFO_ERROR ; 
 int SDHSTS_REW_TIME_OUT ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_finish_data (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_transfer_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  log_dump () ; 
 int /*<<< orphan*/  log_event (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void bcm2835_sdhost_block_irq(struct bcm2835_host *host, u32 intmask)
{
	log_event("IRQK", host->data, intmask);
	if (!host->data) {
		pr_err("%s: got block interrupt 0x%08x even "
			"though no data operation was in progress.\n",
			mmc_hostname(host->mmc), (unsigned)intmask);
		bcm2835_sdhost_dumpregs(host);
		return;
	}

	if (intmask & (SDHSTS_CRC16_ERROR |
		       SDHSTS_FIFO_ERROR |
		       SDHSTS_REW_TIME_OUT)) {
		if (intmask & (SDHSTS_CRC16_ERROR |
			       SDHSTS_FIFO_ERROR))
			host->data->error = -EILSEQ;
		else
			host->data->error = -ETIMEDOUT;

		if (host->debug) {
			log_dump();
			bcm2835_sdhost_dumpregs(host);
		}
	}

	if (!host->dma_desc) {
		BUG_ON(!host->blocks);
		if (host->data->error || (--host->blocks == 0)) {
			bcm2835_sdhost_finish_data(host);
		} else {
			bcm2835_sdhost_transfer_pio(host);
		}
	} else if (host->data->flags & MMC_DATA_WRITE) {
		bcm2835_sdhost_finish_data(host);
	}
}