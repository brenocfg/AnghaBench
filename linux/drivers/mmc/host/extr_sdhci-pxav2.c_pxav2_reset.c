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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sdhci_pxa_platdata {int clk_delay_sel; int clk_delay_cycles; int flags; } ;
struct sdhci_host {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {struct sdhci_pxa_platdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int CLK_GATE_SETTING_BITS ; 
 int PXA_FLAG_ENABLE_CLOCK_GATING ; 
 int SDCLK_DELAY_MASK ; 
 int SDCLK_DELAY_SHIFT ; 
 int SDCLK_SEL_MASK ; 
 int SDCLK_SEL_SHIFT ; 
 scalar_t__ SDHCI_RESET_ALL ; 
 scalar_t__ SD_CLOCK_BURST_SIZE_SETUP ; 
 scalar_t__ SD_FIFO_PARAM ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,scalar_t__) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void pxav2_reset(struct sdhci_host *host, u8 mask)
{
	struct platform_device *pdev = to_platform_device(mmc_dev(host->mmc));
	struct sdhci_pxa_platdata *pdata = pdev->dev.platform_data;

	sdhci_reset(host, mask);

	if (mask == SDHCI_RESET_ALL) {
		u16 tmp = 0;

		/*
		 * tune timing of read data/command when crc error happen
		 * no performance impact
		 */
		if (pdata && pdata->clk_delay_sel == 1) {
			tmp = readw(host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);

			tmp &= ~(SDCLK_DELAY_MASK << SDCLK_DELAY_SHIFT);
			tmp |= (pdata->clk_delay_cycles & SDCLK_DELAY_MASK)
				<< SDCLK_DELAY_SHIFT;
			tmp &= ~(SDCLK_SEL_MASK << SDCLK_SEL_SHIFT);
			tmp |= (1 & SDCLK_SEL_MASK) << SDCLK_SEL_SHIFT;

			writew(tmp, host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
		}

		if (pdata && (pdata->flags & PXA_FLAG_ENABLE_CLOCK_GATING)) {
			tmp = readw(host->ioaddr + SD_FIFO_PARAM);
			tmp &= ~CLK_GATE_SETTING_BITS;
			writew(tmp, host->ioaddr + SD_FIFO_PARAM);
		} else {
			tmp = readw(host->ioaddr + SD_FIFO_PARAM);
			tmp &= ~CLK_GATE_SETTING_BITS;
			tmp |= CLK_GATE_SETTING_BITS;
			writew(tmp, host->ioaddr + SD_FIFO_PARAM);
		}
	}
}