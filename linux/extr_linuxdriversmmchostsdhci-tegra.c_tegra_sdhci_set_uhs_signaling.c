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
struct sdhci_tegra {int ddr_signaling; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_MMC_DDR52 ; 
 unsigned int MMC_TIMING_UHS_DDR50 ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_uhs_signaling (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static void tegra_sdhci_set_uhs_signaling(struct sdhci_host *host,
					  unsigned timing)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);

	if (timing == MMC_TIMING_UHS_DDR50 ||
	    timing == MMC_TIMING_MMC_DDR52)
		tegra_host->ddr_signaling = true;

	sdhci_set_uhs_signaling(host, timing);
}