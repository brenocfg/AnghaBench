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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; scalar_t__ use_dma; int /*<<< orphan*/  base; int /*<<< orphan*/ * data; } ;
struct mmc_request {TYPE_1__* cmd; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int flags; unsigned long long busy_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK ; 
 int MMC_RSP_BUSY ; 
 unsigned long long NSEC_PER_MSEC ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int omap_hsmmc_setup_dma_transfer (struct omap_hsmmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  set_data_timeout (struct omap_hsmmc_host*,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap_hsmmc_prepare_data(struct omap_hsmmc_host *host, struct mmc_request *req)
{
	int ret;
	unsigned long long timeout;

	host->data = req->data;

	if (req->data == NULL) {
		OMAP_HSMMC_WRITE(host->base, BLK, 0);
		if (req->cmd->flags & MMC_RSP_BUSY) {
			timeout = req->cmd->busy_timeout * NSEC_PER_MSEC;

			/*
			 * Set an arbitrary 100ms data timeout for commands with
			 * busy signal and no indication of busy_timeout.
			 */
			if (!timeout)
				timeout = 100000000U;

			set_data_timeout(host, timeout, 0);
		}
		return 0;
	}

	if (host->use_dma) {
		ret = omap_hsmmc_setup_dma_transfer(host, req);
		if (ret != 0) {
			dev_err(mmc_dev(host->mmc), "MMC start dma failure\n");
			return ret;
		}
	}
	return 0;
}