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
struct mmc_data {int bytes_xfered; int blksz; int blocks; scalar_t__ stop; scalar_t__ error; } ;
struct bcm2835_host {int wait_for_dma; int /*<<< orphan*/  finish_tasklet; scalar_t__ use_dma; TYPE_1__* mrq; struct mmc_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  bcm2835_mmc_reset (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_send_command (struct bcm2835_host*,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_mmc_finish_data(struct bcm2835_host *host)
{
	struct mmc_data *data;

	BUG_ON(!host->data);

	data = host->data;
	host->data = NULL;

	if (data->error)
		data->bytes_xfered = 0;
	else
		data->bytes_xfered = data->blksz * data->blocks;

	/*
	 * Need to send CMD12 if -
	 * a) open-ended multiblock transfer (no CMD23)
	 * b) error in multiblock transfer
	 */
	if (data->stop &&
	    (data->error ||
	     !host->mrq->sbc)) {

		/*
		 * The controller needs a reset of internal state machines
		 * upon error conditions.
		 */
		if (data->error) {
			bcm2835_mmc_reset(host, SDHCI_RESET_CMD);
			bcm2835_mmc_reset(host, SDHCI_RESET_DATA);
		}

		bcm2835_mmc_send_command(host, data->stop);
	} else if (host->use_dma) {
		host->wait_for_dma = true;
	} else {
		tasklet_schedule(&host->finish_tasklet);
	}
}