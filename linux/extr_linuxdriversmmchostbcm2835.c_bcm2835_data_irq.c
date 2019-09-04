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
typedef  int /*<<< orphan*/  u32 ;
struct bcm2835_host {int hcfg; scalar_t__ blocks; scalar_t__ ioaddr; TYPE_1__* data; } ;
struct TYPE_2__ {int flags; scalar_t__ error; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 scalar_t__ SDHCFG ; 
 int SDHCFG_BLOCK_IRPT_EN ; 
 int SDHCFG_DATA_IRPT_EN ; 
 int /*<<< orphan*/  bcm2835_check_data_error (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_transfer_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm2835_data_irq(struct bcm2835_host *host, u32 intmask)
{
	/* There are no dedicated data/space available interrupt
	 * status bits, so it is necessary to use the single shared
	 * data/space available FIFO status bits. It is therefore not
	 * an error to get here when there is no data transfer in
	 * progress.
	 */
	if (!host->data)
		return;

	bcm2835_check_data_error(host, intmask);
	if (host->data->error)
		goto finished;

	if (host->data->flags & MMC_DATA_WRITE) {
		/* Use the block interrupt for writes after the first block */
		host->hcfg &= ~(SDHCFG_DATA_IRPT_EN);
		host->hcfg |= SDHCFG_BLOCK_IRPT_EN;
		writel(host->hcfg, host->ioaddr + SDHCFG);
		bcm2835_transfer_pio(host);
	} else {
		bcm2835_transfer_pio(host);
		host->blocks--;
		if ((host->blocks == 0) || host->data->error)
			goto finished;
	}
	return;

finished:
	host->hcfg &= ~(SDHCFG_DATA_IRPT_EN | SDHCFG_BLOCK_IRPT_EN);
	writel(host->hcfg, host->ioaddr + SDHCFG);
}