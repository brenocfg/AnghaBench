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
struct sdhci_host {struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 unsigned char MMC_POWER_OFF ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int /*<<< orphan*/  SDHCI_POWER_ON ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_power_reg(struct sdhci_host *host, unsigned char mode,
				unsigned short vdd)
{
	struct mmc_host *mmc = host->mmc;

	mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);

	if (mode != MMC_POWER_OFF)
		sdhci_writeb(host, SDHCI_POWER_ON, SDHCI_POWER_CONTROL);
	else
		sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
}