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
typedef  int /*<<< orphan*/  u64 ;
struct iommu_ops {int dummy; } ;
struct TYPE_2__ {int dma_coherent; } ;
struct device {TYPE_1__ archdata; int /*<<< orphan*/ * dma_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iommu_setup_dma_ops (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iommu_ops const*) ; 
 int /*<<< orphan*/  arm64_swiotlb_dma_ops ; 

void arch_setup_dma_ops(struct device *dev, u64 dma_base, u64 size,
			const struct iommu_ops *iommu, bool coherent)
{
	if (!dev->dma_ops)
		dev->dma_ops = &arm64_swiotlb_dma_ops;

	dev->archdata.dma_coherent = coherent;
	__iommu_setup_dma_ops(dev, dma_base, size, iommu);

#ifdef CONFIG_XEN
	if (xen_initial_domain()) {
		dev->archdata.dev_dma_ops = dev->dma_ops;
		dev->dma_ops = xen_dma_ops;
	}
#endif
}