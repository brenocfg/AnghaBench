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
typedef  int u64 ;
struct iommu {int dma_addr_mask; } ;
struct TYPE_2__ {struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 

__attribute__((used)) static int dma_4u_supported(struct device *dev, u64 device_mask)
{
	struct iommu *iommu = dev->archdata.iommu;

	if (device_mask > DMA_BIT_MASK(32))
		return 0;
	if ((device_mask & iommu->dma_addr_mask) == iommu->dma_addr_mask)
		return 1;
#ifdef CONFIG_PCI
	if (dev_is_pci(dev))
		return pci64_dma_supported(to_pci_dev(dev), device_mask);
#endif
	return 0;
}