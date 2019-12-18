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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  ESDHC_DMA_SNOOP ; 
 int /*<<< orphan*/  ESDHC_DMA_SYSCTL ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct device* mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_dma_is_coherent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esdhc_of_enable_dma(struct sdhci_host *host)
{
	u32 value;
	struct device *dev = mmc_dev(host->mmc);

	if (of_device_is_compatible(dev->of_node, "fsl,ls1043a-esdhc") ||
	    of_device_is_compatible(dev->of_node, "fsl,ls1046a-esdhc"))
		dma_set_mask_and_coherent(dev, DMA_BIT_MASK(40));

	value = sdhci_readl(host, ESDHC_DMA_SYSCTL);

	if (of_dma_is_coherent(dev->of_node))
		value |= ESDHC_DMA_SNOOP;
	else
		value &= ~ESDHC_DMA_SNOOP;

	sdhci_writel(host, value, ESDHC_DMA_SYSCTL);
	return 0;
}