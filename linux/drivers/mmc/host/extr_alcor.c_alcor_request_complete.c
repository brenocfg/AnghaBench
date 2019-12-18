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
struct mmc_request {int dummy; } ;
struct alcor_sdmmc_host {scalar_t__ dma_on; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; struct mmc_request* mrq; int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_from_priv (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 

__attribute__((used)) static void alcor_request_complete(struct alcor_sdmmc_host *host,
				   bool cancel_timeout)
{
	struct mmc_request *mrq;

	/*
	 * If this work gets rescheduled while running, it will
	 * be run again afterwards but without any active request.
	 */
	if (!host->mrq)
		return;

	if (cancel_timeout)
		cancel_delayed_work(&host->timeout_work);

	mrq = host->mrq;

	host->mrq = NULL;
	host->cmd = NULL;
	host->data = NULL;
	host->dma_on = 0;

	mmc_request_done(mmc_from_priv(host), mrq);
}