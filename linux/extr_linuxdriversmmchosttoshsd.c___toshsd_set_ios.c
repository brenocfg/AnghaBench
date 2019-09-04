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
typedef  int u16 ;
struct toshsd_host {scalar_t__ ioaddr; int /*<<< orphan*/  pdev; } ;
struct mmc_ios {int clock; int power_mode; int bus_width; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int HCLK ; 
#define  MMC_BUS_WIDTH_1 132 
#define  MMC_BUS_WIDTH_4 131 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int SD_CARDCLK_DIV_DISABLE ; 
 int SD_CARDCLK_ENABLE_CLOCK ; 
 scalar_t__ SD_CARDCLOCKCTRL ; 
 scalar_t__ SD_CARDOPTIONSETUP ; 
 int SD_CARDOPT_C2_MODULE_ABSENT ; 
 int SD_CARDOPT_DATA_RESP_TIMEOUT (int) ; 
 int SD_CARDOPT_DATA_XFR_WIDTH_1 ; 
 int SD_CARDOPT_DATA_XFR_WIDTH_4 ; 
 int SD_CARDOPT_REQUIRED ; 
 int /*<<< orphan*/  SD_PCICFG_CLKMODE ; 
 int /*<<< orphan*/  SD_PCICFG_CLKMODE_DIV_DISABLE ; 
 int /*<<< orphan*/  SD_PCICFG_POWER1 ; 
 int /*<<< orphan*/  SD_PCICFG_POWER2 ; 
 int /*<<< orphan*/  SD_PCICFG_PWR1_33V ; 
 int /*<<< orphan*/  SD_PCICFG_PWR1_OFF ; 
 int /*<<< orphan*/  SD_PCICFG_PWR2_AUTO ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct toshsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __toshsd_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct toshsd_host *host = mmc_priv(mmc);

	if (ios->clock) {
		u16 clk;
		int div = 1;

		while (ios->clock < HCLK / div)
			div *= 2;

		clk = div >> 2;

		if (div == 1) { /* disable the divider */
			pci_write_config_byte(host->pdev, SD_PCICFG_CLKMODE,
					      SD_PCICFG_CLKMODE_DIV_DISABLE);
			clk |= SD_CARDCLK_DIV_DISABLE;
		} else
			pci_write_config_byte(host->pdev, SD_PCICFG_CLKMODE, 0);

		clk |= SD_CARDCLK_ENABLE_CLOCK;
		iowrite16(clk, host->ioaddr + SD_CARDCLOCKCTRL);

		mdelay(10);
	} else
		iowrite16(0, host->ioaddr + SD_CARDCLOCKCTRL);

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		pci_write_config_byte(host->pdev, SD_PCICFG_POWER1,
					SD_PCICFG_PWR1_OFF);
		mdelay(1);
		break;
	case MMC_POWER_UP:
		break;
	case MMC_POWER_ON:
		pci_write_config_byte(host->pdev, SD_PCICFG_POWER1,
					SD_PCICFG_PWR1_33V);
		pci_write_config_byte(host->pdev, SD_PCICFG_POWER2,
					SD_PCICFG_PWR2_AUTO);
		mdelay(20);
		break;
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		iowrite16(SD_CARDOPT_REQUIRED | SD_CARDOPT_DATA_RESP_TIMEOUT(14)
				| SD_CARDOPT_C2_MODULE_ABSENT
				| SD_CARDOPT_DATA_XFR_WIDTH_1,
				host->ioaddr + SD_CARDOPTIONSETUP);
		break;
	case MMC_BUS_WIDTH_4:
		iowrite16(SD_CARDOPT_REQUIRED | SD_CARDOPT_DATA_RESP_TIMEOUT(14)
				| SD_CARDOPT_C2_MODULE_ABSENT
				| SD_CARDOPT_DATA_XFR_WIDTH_4,
				host->ioaddr + SD_CARDOPTIONSETUP);
		break;
	}
}