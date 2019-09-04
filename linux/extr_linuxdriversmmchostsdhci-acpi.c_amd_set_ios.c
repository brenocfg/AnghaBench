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
struct sdhci_host {unsigned int timing; } ;
struct mmc_ios {unsigned int timing; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_MMC_HS ; 
 unsigned int MMC_TIMING_MMC_HS200 ; 
 unsigned int MMC_TIMING_MMC_HS400 ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdhci_acpi_amd_hs400_dll (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_ios (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	unsigned int old_timing = host->timing;

	sdhci_set_ios(mmc, ios);
	if (old_timing == MMC_TIMING_MMC_HS200 &&
	    ios->timing == MMC_TIMING_MMC_HS)
		sdhci_writew(host, 0x9, SDHCI_HOST_CONTROL2);
	if (old_timing != MMC_TIMING_MMC_HS400 &&
	    ios->timing == MMC_TIMING_MMC_HS400) {
		sdhci_writew(host, 0x80, SDHCI_HOST_CONTROL2);
		sdhci_acpi_amd_hs400_dll(host);
	}
}