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
struct sdhci_tegra_soc_data {scalar_t__ dma_mask; } ;
struct sdhci_tegra {struct sdhci_tegra_soc_data* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int dma_set_mask_and_coherent (struct device*,scalar_t__) ; 
 struct device* mmc_dev (int /*<<< orphan*/ ) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int tegra_sdhci_set_dma_mask(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *platform = sdhci_priv(host);
	struct sdhci_tegra *tegra = sdhci_pltfm_priv(platform);
	const struct sdhci_tegra_soc_data *soc = tegra->soc_data;
	struct device *dev = mmc_dev(host->mmc);

	if (soc->dma_mask)
		return dma_set_mask_and_coherent(dev, soc->dma_mask);

	return 0;
}