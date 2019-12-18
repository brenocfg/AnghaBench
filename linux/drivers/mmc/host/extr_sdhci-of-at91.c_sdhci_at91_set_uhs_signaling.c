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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_MMC_DDR52 ; 
 int /*<<< orphan*/  SDMMC_MC1R ; 
 int /*<<< orphan*/  SDMMC_MC1R_DDR ; 
 int /*<<< orphan*/  sdhci_set_uhs_signaling (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_at91_set_uhs_signaling(struct sdhci_host *host,
					 unsigned int timing)
{
	if (timing == MMC_TIMING_MMC_DDR52)
		sdhci_writeb(host, SDMMC_MC1R_DDR, SDMMC_MC1R);
	sdhci_set_uhs_signaling(host, timing);
}