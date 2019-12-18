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
struct mmc_ios {int power_mode; int bus_width; int /*<<< orphan*/  vdd; int /*<<< orphan*/  clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  cmdat; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MMC_CMDAT_BUS_WIDTH_4BIT ; 
 int /*<<< orphan*/  JZ_MMC_CMDAT_INIT ; 
#define  MMC_BUS_WIDTH_1 131 
#define  MMC_BUS_WIDTH_4 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_mmc_reset (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_set_clock_rate (struct jz4740_mmc_host*,int /*<<< orphan*/ ) ; 
 struct jz4740_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4740_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct jz4740_mmc_host *host = mmc_priv(mmc);
	if (ios->clock)
		jz4740_mmc_set_clock_rate(host, ios->clock);

	switch (ios->power_mode) {
	case MMC_POWER_UP:
		jz4740_mmc_reset(host);
		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		host->cmdat |= JZ_MMC_CMDAT_INIT;
		clk_prepare_enable(host->clk);
		break;
	case MMC_POWER_ON:
		break;
	default:
		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		clk_disable_unprepare(host->clk);
		break;
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_4BIT;
		break;
	case MMC_BUS_WIDTH_4:
		host->cmdat |= JZ_MMC_CMDAT_BUS_WIDTH_4BIT;
		break;
	default:
		break;
	}
}