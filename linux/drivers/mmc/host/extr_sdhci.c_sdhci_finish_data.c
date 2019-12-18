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
struct sdhci_host {int flags; struct mmc_command* cmd; struct mmc_command* data_cmd; struct mmc_data* data; } ;
struct mmc_data {int bytes_xfered; int blksz; int blocks; TYPE_1__* mrq; scalar_t__ stop; scalar_t__ error; } ;
struct mmc_command {int dummy; } ;
struct TYPE_2__ {scalar_t__ cap_cmd_during_tfr; int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int SDHCI_REQ_USE_DMA ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int SDHCI_USE_ADMA ; 
 int /*<<< orphan*/  __sdhci_finish_mrq (struct sdhci_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  sdhci_adma_table_post (struct sdhci_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_send_command (struct sdhci_host*,scalar_t__) ; 

__attribute__((used)) static void sdhci_finish_data(struct sdhci_host *host)
{
	struct mmc_command *data_cmd = host->data_cmd;
	struct mmc_data *data = host->data;

	host->data = NULL;
	host->data_cmd = NULL;

	/*
	 * The controller needs a reset of internal state machines upon error
	 * conditions.
	 */
	if (data->error) {
		if (!host->cmd || host->cmd == data_cmd)
			sdhci_do_reset(host, SDHCI_RESET_CMD);
		sdhci_do_reset(host, SDHCI_RESET_DATA);
	}

	if ((host->flags & (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA)) ==
	    (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA))
		sdhci_adma_table_post(host, data);

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
	     !data->mrq->sbc)) {
		/*
		 * 'cap_cmd_during_tfr' request must not use the command line
		 * after mmc_command_done() has been called. It is upper layer's
		 * responsibility to send the stop command if required.
		 */
		if (data->mrq->cap_cmd_during_tfr) {
			__sdhci_finish_mrq(host, data->mrq);
		} else {
			/* Avoid triggering warning in sdhci_send_command() */
			host->cmd = NULL;
			sdhci_send_command(host, data->stop);
		}
	} else {
		__sdhci_finish_mrq(host, data->mrq);
	}
}