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
struct sdhci_host {int quirks2; int flags; struct mmc_host* mmc; } ;
struct mmc_host {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int SDHCI_QUIRK2_BROKEN_64_BIT_DMA ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct device* mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_set_dma_mask(struct sdhci_host *host)
{
	struct mmc_host *mmc = host->mmc;
	struct device *dev = mmc_dev(mmc);
	int ret = -EINVAL;

	if (host->quirks2 & SDHCI_QUIRK2_BROKEN_64_BIT_DMA)
		host->flags &= ~SDHCI_USE_64_BIT_DMA;

	/* Try 64-bit mask if hardware is capable  of it */
	if (host->flags & SDHCI_USE_64_BIT_DMA) {
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
		if (ret) {
			pr_warn("%s: Failed to set 64-bit DMA mask.\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_64_BIT_DMA;
		}
	}

	/* 32-bit mask as default & fallback */
	if (ret) {
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		if (ret)
			pr_warn("%s: Failed to set 32-bit DMA mask.\n",
				mmc_hostname(mmc));
	}

	return ret;
}