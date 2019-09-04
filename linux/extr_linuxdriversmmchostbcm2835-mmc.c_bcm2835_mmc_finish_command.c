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
struct bcm2835_host {TYPE_2__* cmd; int /*<<< orphan*/  finish_tasklet; scalar_t__ data_early; scalar_t__ data; scalar_t__ use_dma; TYPE_1__* mrq; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {int flags; int* resp; int /*<<< orphan*/  data; scalar_t__ error; } ;
struct TYPE_4__ {TYPE_3__* cmd; TYPE_2__* sbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ SDHCI_RESPONSE ; 
 int /*<<< orphan*/  bcm2835_mmc_finish_data (struct bcm2835_host*) ; 
 int bcm2835_mmc_readb (struct bcm2835_host*,scalar_t__) ; 
 int bcm2835_mmc_readl (struct bcm2835_host*,scalar_t__) ; 
 int /*<<< orphan*/  bcm2835_mmc_send_command (struct bcm2835_host*,TYPE_3__*) ; 
 int /*<<< orphan*/  bcm2835_mmc_transfer_dma (struct bcm2835_host*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_mmc_finish_command(struct bcm2835_host *host)
{
	int i;

	BUG_ON(host->cmd == NULL);

	if (host->cmd->flags & MMC_RSP_PRESENT) {
		if (host->cmd->flags & MMC_RSP_136) {
			/* CRC is stripped so we need to do some shifting. */
			for (i = 0; i < 4; i++) {
				host->cmd->resp[i] = bcm2835_mmc_readl(host,
					SDHCI_RESPONSE + (3-i)*4) << 8;
				if (i != 3)
					host->cmd->resp[i] |=
						bcm2835_mmc_readb(host,
						SDHCI_RESPONSE + (3-i)*4-1);
			}
		} else {
			host->cmd->resp[0] = bcm2835_mmc_readl(host, SDHCI_RESPONSE);
		}
	}

	host->cmd->error = 0;

	/* Finished CMD23, now send actual command. */
	if (host->cmd == host->mrq->sbc) {
		host->cmd = NULL;
		bcm2835_mmc_send_command(host, host->mrq->cmd);

		if (host->mrq->cmd->data && host->use_dma) {
			/* DMA transfer starts now, PIO starts after interrupt */
			bcm2835_mmc_transfer_dma(host);
		}
	} else {

		/* Processed actual command. */
		if (host->data && host->data_early)
			bcm2835_mmc_finish_data(host);

		if (!host->cmd->data)
			tasklet_schedule(&host->finish_tasklet);

		host->cmd = NULL;
	}
}