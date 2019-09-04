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
struct mmc_data {scalar_t__ error; scalar_t__ stop; } ;
struct bcm2835_host {int cmd; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  stop_time; scalar_t__ delay_after_this_stop; int /*<<< orphan*/  use_busy; TYPE_1__* mrq; int /*<<< orphan*/  use_sbc; struct mmc_data* data; int /*<<< orphan*/  data_complete; } ;
struct TYPE_2__ {scalar_t__ stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bcm2835_sdhost_finish_command (struct bcm2835_host*,int /*<<< orphan*/ *) ; 
 scalar_t__ bcm2835_sdhost_send_command (struct bcm2835_host*,scalar_t__) ; 
 int /*<<< orphan*/  bcm2835_sdhost_wait_transfer_complete (struct bcm2835_host*) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_event (char*,struct mmc_data*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_sdhost_transfer_complete(struct bcm2835_host *host)
{
	struct mmc_data *data;

	BUG_ON(host->cmd);
	BUG_ON(!host->data);
	BUG_ON(!host->data_complete);

	data = host->data;
	host->data = NULL;

	log_event("TCM<", data, data->error);
	pr_debug("transfer_complete(error %d, stop %d)\n",
	       data->error, data->stop ? 1 : 0);

	/*
	 * Need to send CMD12 if -
	 * a) open-ended multiblock transfer (no CMD23)
	 * b) error in multiblock transfer
	 */
	if (host->mrq->stop && (data->error || !host->use_sbc)) {
		if (bcm2835_sdhost_send_command(host, host->mrq->stop)) {
			/* No busy, so poll for completion */
			if (!host->use_busy)
				bcm2835_sdhost_finish_command(host, NULL);

			if (host->delay_after_this_stop)
				do_gettimeofday(&host->stop_time);
		}
	} else {
		bcm2835_sdhost_wait_transfer_complete(host);
		tasklet_schedule(&host->finish_tasklet);
	}
	log_event("TCM>", data, 0);
}