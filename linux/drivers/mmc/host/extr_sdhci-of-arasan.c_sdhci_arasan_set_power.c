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
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  sdhci_set_power_noreg (struct sdhci_host*,unsigned char,unsigned short) ; 

__attribute__((used)) static void sdhci_arasan_set_power(struct sdhci_host *host, unsigned char mode,
		     unsigned short vdd)
{
	if (!IS_ERR(host->mmc->supply.vmmc)) {
		struct mmc_host *mmc = host->mmc;

		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
	}
	sdhci_set_power_noreg(host, mode, vdd);
}