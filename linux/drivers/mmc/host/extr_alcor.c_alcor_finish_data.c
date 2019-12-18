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
struct alcor_sdmmc_host {TYPE_1__* mrq; scalar_t__ dma_on; struct mmc_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int AU6601_RESET_CMD ; 
 int AU6601_RESET_DATA ; 
 int /*<<< orphan*/  alcor_request_complete (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_reset (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_send_cmd (struct alcor_sdmmc_host*,scalar_t__,int) ; 
 int /*<<< orphan*/  alcor_unmask_sd_irqs (struct alcor_sdmmc_host*) ; 

__attribute__((used)) static void alcor_finish_data(struct alcor_sdmmc_host *host)
{
	struct mmc_data *data;

	data = host->data;
	host->data = NULL;
	host->dma_on = 0;

	/*
	 * The specification states that the block count register must
	 * be updated, but it does not specify at what point in the
	 * data flow. That makes the register entirely useless to read
	 * back so we have to assume that nothing made it to the card
	 * in the event of an error.
	 */
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
		if (data->error)
			alcor_reset(host, AU6601_RESET_CMD | AU6601_RESET_DATA);

		alcor_unmask_sd_irqs(host);
		alcor_send_cmd(host, data->stop, false);
		return;
	}

	alcor_request_complete(host, 1);
}