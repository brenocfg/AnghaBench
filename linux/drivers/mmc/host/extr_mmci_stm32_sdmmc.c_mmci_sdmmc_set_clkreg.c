#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmci_host {unsigned int mclk; int cclk; unsigned int clk_reg_add; TYPE_2__* mmc; } ;
struct TYPE_3__ {scalar_t__ timing; scalar_t__ power_mode; scalar_t__ bus_width; } ;
struct TYPE_4__ {int actual_clock; TYPE_1__ ios; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int) ; 
 unsigned int MCI_STM32_CLK_BUSSPEED ; 
 unsigned int MCI_STM32_CLK_CLKDIV_MSK ; 
 unsigned int MCI_STM32_CLK_DDR ; 
 unsigned int MCI_STM32_CLK_HWFCEN ; 
 unsigned int MCI_STM32_CLK_SELFBCK ; 
 unsigned int MCI_STM32_CLK_SEL_MSK ; 
 unsigned int MCI_STM32_CLK_WIDEBUS_4 ; 
 unsigned int MCI_STM32_CLK_WIDEBUS_8 ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 scalar_t__ MMC_POWER_ON ; 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 scalar_t__ MMC_TIMING_UHS_SDR50 ; 
 int /*<<< orphan*/  mmci_write_clkreg (struct mmci_host*,unsigned int) ; 

__attribute__((used)) static void mmci_sdmmc_set_clkreg(struct mmci_host *host, unsigned int desired)
{
	unsigned int clk = 0, ddr = 0;

	if (host->mmc->ios.timing == MMC_TIMING_MMC_DDR52 ||
	    host->mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		ddr = MCI_STM32_CLK_DDR;

	/*
	 * cclk = mclk / (2 * clkdiv)
	 * clkdiv 0 => bypass
	 * in ddr mode bypass is not possible
	 */
	if (desired) {
		if (desired >= host->mclk && !ddr) {
			host->cclk = host->mclk;
		} else {
			clk = DIV_ROUND_UP(host->mclk, 2 * desired);
			if (clk > MCI_STM32_CLK_CLKDIV_MSK)
				clk = MCI_STM32_CLK_CLKDIV_MSK;
			host->cclk = host->mclk / (2 * clk);
		}
	} else {
		/*
		 * while power-on phase the clock can't be define to 0,
		 * Only power-off and power-cyc deactivate the clock.
		 * if desired clock is 0, set max divider
		 */
		clk = MCI_STM32_CLK_CLKDIV_MSK;
		host->cclk = host->mclk / (2 * clk);
	}

	/* Set actual clock for debug */
	if (host->mmc->ios.power_mode == MMC_POWER_ON)
		host->mmc->actual_clock = host->cclk;
	else
		host->mmc->actual_clock = 0;

	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		clk |= MCI_STM32_CLK_WIDEBUS_4;
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		clk |= MCI_STM32_CLK_WIDEBUS_8;

	clk |= MCI_STM32_CLK_HWFCEN;
	clk |= host->clk_reg_add;
	clk |= ddr;

	/*
	 * SDMMC_FBCK is selected when an external Delay Block is needed
	 * with SDR104.
	 */
	if (host->mmc->ios.timing >= MMC_TIMING_UHS_SDR50) {
		clk |= MCI_STM32_CLK_BUSSPEED;
		if (host->mmc->ios.timing == MMC_TIMING_UHS_SDR104) {
			clk &= ~MCI_STM32_CLK_SEL_MSK;
			clk |= MCI_STM32_CLK_SELFBCK;
		}
	}

	mmci_write_clkreg(host, clk);
}