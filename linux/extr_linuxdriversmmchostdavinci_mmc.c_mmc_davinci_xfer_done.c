#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mmc_davinci_host {int do_dma; int active_request; scalar_t__ base; TYPE_2__* mmc; TYPE_1__* cmd; int /*<<< orphan*/  data_dir; scalar_t__ sdio_int; int /*<<< orphan*/ * data; } ;
struct mmc_data {int /*<<< orphan*/  stop; int /*<<< orphan*/  mrq; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_6__ {int caps; } ;
struct TYPE_5__ {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCIM ; 
 int /*<<< orphan*/  DAVINCI_MMC_DATADIR_NONE ; 
 scalar_t__ DAVINCI_SDIOIST ; 
 scalar_t__ DAVINCI_SDIOST0 ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  SDIOIST_IOINT ; 
 int SDIOST0_DAT1_HI ; 
 int /*<<< orphan*/  davinci_abort_dma (struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_davinci_start_command (struct mmc_davinci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_request_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (TYPE_2__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mmc_davinci_xfer_done(struct mmc_davinci_host *host, struct mmc_data *data)
{
	host->data = NULL;

	if (host->mmc->caps & MMC_CAP_SDIO_IRQ) {
		/*
		 * SDIO Interrupt Detection work-around as suggested by
		 * Davinci Errata (TMS320DM355 Silicon Revision 1.1 Errata
		 * 2.1.6): Signal SDIO interrupt only if it is enabled by core
		 */
		if (host->sdio_int && !(readl(host->base + DAVINCI_SDIOST0) &
					SDIOST0_DAT1_HI)) {
			writel(SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
			mmc_signal_sdio_irq(host->mmc);
		}
	}

	if (host->do_dma) {
		davinci_abort_dma(host);

		dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		host->do_dma = false;
	}
	host->data_dir = DAVINCI_MMC_DATADIR_NONE;

	if (!data->stop || (host->cmd && host->cmd->error)) {
		mmc_request_done(host->mmc, data->mrq);
		writel(0, host->base + DAVINCI_MMCIM);
		host->active_request = false;
	} else
		mmc_davinci_start_command(host, data->stop);
}