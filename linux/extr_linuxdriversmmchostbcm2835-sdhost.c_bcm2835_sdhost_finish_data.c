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
struct mmc_data {int bytes_xfered; int blksz; int blocks; scalar_t__ error; scalar_t__ stop; } ;
struct bcm2835_host {int hcfg; int data_complete; scalar_t__ cmd; TYPE_1__* mrq; struct mmc_data* data; } ;
struct TYPE_2__ {scalar_t__ sbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SDHCFG ; 
 int SDHCFG_BLOCK_IRPT_EN ; 
 int SDHCFG_DATA_IRPT_EN ; 
 int /*<<< orphan*/  SDHSTS ; 
 int /*<<< orphan*/  bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_transfer_complete (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_event (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void bcm2835_sdhost_finish_data(struct bcm2835_host *host)
{
	struct mmc_data *data;

	data = host->data;
	BUG_ON(!data);

	log_event("FDA<", host->mrq, host->cmd);
	pr_debug("finish_data(error %d, stop %d, sbc %d)\n",
	       data->error, data->stop ? 1 : 0,
	       host->mrq->sbc ? 1 : 0);

	host->hcfg &= ~(SDHCFG_DATA_IRPT_EN | SDHCFG_BLOCK_IRPT_EN);
	bcm2835_sdhost_write(host, host->hcfg, SDHCFG);

	data->bytes_xfered = data->error ? 0 : (data->blksz * data->blocks);

	host->data_complete = 1;

	if (host->cmd) {
		/*
		 * Data managed to finish before the
		 * command completed. Make sure we do
		 * things in the proper order.
		 */
		pr_debug("Finished early - HSTS %x\n",
			 bcm2835_sdhost_read(host, SDHSTS));
	}
	else
		bcm2835_sdhost_transfer_complete(host);
	log_event("FDA>", host->mrq, host->cmd);
}