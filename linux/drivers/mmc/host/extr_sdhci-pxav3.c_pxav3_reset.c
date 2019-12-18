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
struct sdhci_pxa_platdata {scalar_t__ clk_delay_cycles; } ;
struct sdhci_host {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {struct sdhci_pxa_platdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int SDCLK_DELAY_MASK ; 
 int SDCLK_DELAY_SHIFT ; 
 int SDCLK_SEL ; 
 scalar_t__ SDHCI_RESET_ALL ; 
 scalar_t__ SD_CLOCK_BURST_SIZE_SETUP ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,scalar_t__) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void pxav3_reset(struct sdhci_host *host, u8 mask)
{
	struct platform_device *pdev = to_platform_device(mmc_dev(host->mmc));
	struct sdhci_pxa_platdata *pdata = pdev->dev.platform_data;

	sdhci_reset(host, mask);

	if (mask == SDHCI_RESET_ALL) {
		/*
		 * tune timing of read data/command when crc error happen
		 * no performance impact
		 */
		if (pdata && 0 != pdata->clk_delay_cycles) {
			u16 tmp;

			tmp = readw(host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
			tmp |= (pdata->clk_delay_cycles & SDCLK_DELAY_MASK)
				<< SDCLK_DELAY_SHIFT;
			tmp |= SDCLK_SEL;
			writew(tmp, host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
		}
	}
}