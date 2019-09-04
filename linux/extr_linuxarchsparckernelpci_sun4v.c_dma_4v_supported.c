#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct iommu {int dma_addr_mask; TYPE_2__* atu; } ;
struct TYPE_3__ {struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct TYPE_4__ {int dma_addr_mask; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int pci64_dma_supported (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static int dma_4v_supported(struct device *dev, u64 device_mask)
{
	struct iommu *iommu = dev->archdata.iommu;
	u64 dma_addr_mask = iommu->dma_addr_mask;

	if (device_mask > DMA_BIT_MASK(32)) {
		if (iommu->atu)
			dma_addr_mask = iommu->atu->dma_addr_mask;
		else
			return 0;
	}

	if ((device_mask & dma_addr_mask) == dma_addr_mask)
		return 1;
	return pci64_dma_supported(to_pci_dev(dev), device_mask);
}