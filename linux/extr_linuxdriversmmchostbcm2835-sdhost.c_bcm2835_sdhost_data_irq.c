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
struct bcm2835_host {scalar_t__ blocks; TYPE_1__* data; int /*<<< orphan*/  hcfg; scalar_t__ debug; } ;
struct TYPE_2__ {int error; int flags; } ;

/* Variables and functions */
 int EILSEQ ; 
 int ETIMEDOUT ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  SDHCFG ; 
 int /*<<< orphan*/  SDHCFG_BLOCK_IRPT_EN ; 
 int /*<<< orphan*/  SDHCFG_DATA_IRPT_EN ; 
 int SDHSTS_CRC16_ERROR ; 
 int SDHSTS_FIFO_ERROR ; 
 int SDHSTS_REW_TIME_OUT ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_finish_data (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_transfer_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dump () ; 
 int /*<<< orphan*/  log_event (char*,TYPE_1__*,int) ; 

__attribute__((used)) static void bcm2835_sdhost_data_irq(struct bcm2835_host *host, u32 intmask)
{
	/* There are no dedicated data/space available interrupt
	   status bits, so it is necessary to use the single shared
	   data/space available FIFO status bits. It is therefore not
	   an error to get here when there is no data transfer in
	   progress. */
	log_event("IRQD", host->data, intmask);
	if (!host->data)
		return;

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

	if (host->data->error) {
		bcm2835_sdhost_finish_data(host);
	} else if (host->data->flags & MMC_DATA_WRITE) {
		/* Use the block interrupt for writes after the first block */
		host->hcfg &= ~(SDHCFG_DATA_IRPT_EN);
		host->hcfg |= SDHCFG_BLOCK_IRPT_EN;
		bcm2835_sdhost_write(host, host->hcfg, SDHCFG);
		bcm2835_sdhost_transfer_pio(host);
	} else {
		bcm2835_sdhost_transfer_pio(host);
		host->blocks--;
		if ((host->blocks == 0) || host->data->error)
			bcm2835_sdhost_finish_data(host);
	}
}