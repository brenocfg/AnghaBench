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
struct mxcmci_host {int burstlen; scalar_t__ power_mode; int /*<<< orphan*/  clock; int /*<<< orphan*/  cmdat; int /*<<< orphan*/ * dma; scalar_t__ do_dma; int /*<<< orphan*/  mmc; } ;
struct mmc_ios {scalar_t__ bus_width; scalar_t__ power_mode; int /*<<< orphan*/  clock; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DAT_CONT_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  CMD_DAT_CONT_INIT ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_POWER_ON ; 
 int /*<<< orphan*/  MMC_REG_STR_STP_CLK ; 
 int /*<<< orphan*/  STR_STP_CLK_START_CLK ; 
 int /*<<< orphan*/  STR_STP_CLK_STOP_CLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mxcmci_set_clk_rate (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_set_power (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int mxcmci_setup_dma (struct mmc_host*) ; 
 scalar_t__ mxcmci_use_dma (struct mxcmci_host*) ; 
 int /*<<< orphan*/  mxcmci_writew (struct mxcmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxcmci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mxcmci_host *host = mmc_priv(mmc);
	int burstlen, ret;

	/*
	 * use burstlen of 64 (16 words) in 4 bit mode (--> reg value  0)
	 * use burstlen of 16 (4 words) in 1 bit mode (--> reg value 16)
	 */
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		burstlen = 16;
	else
		burstlen = 4;

	if (mxcmci_use_dma(host) && burstlen != host->burstlen) {
		host->burstlen = burstlen;
		ret = mxcmci_setup_dma(mmc);
		if (ret) {
			dev_err(mmc_dev(host->mmc),
				"failed to config DMA channel. Falling back to PIO\n");
			dma_release_channel(host->dma);
			host->do_dma = 0;
			host->dma = NULL;
		}
	}

	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMD_DAT_CONT_BUS_WIDTH_4;
	else
		host->cmdat &= ~CMD_DAT_CONT_BUS_WIDTH_4;

	if (host->power_mode != ios->power_mode) {
		host->power_mode = ios->power_mode;
		mxcmci_set_power(host, ios->vdd);

		if (ios->power_mode == MMC_POWER_ON)
			host->cmdat |= CMD_DAT_CONT_INIT;
	}

	if (ios->clock) {
		mxcmci_set_clk_rate(host, ios->clock);
		mxcmci_writew(host, STR_STP_CLK_START_CLK, MMC_REG_STR_STP_CLK);
	} else {
		mxcmci_writew(host, STR_STP_CLK_STOP_CLK, MMC_REG_STR_STP_CLK);
	}

	host->clock = ios->clock;
}