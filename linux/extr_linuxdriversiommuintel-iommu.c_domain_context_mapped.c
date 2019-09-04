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
typedef  int /*<<< orphan*/  u8 ;
struct intel_iommu {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int device_context_mapped (struct intel_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_iommu* device_to_iommu (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_context_mapped_cb ; 
 int /*<<< orphan*/  pci_for_each_dma_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intel_iommu*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static int domain_context_mapped(struct device *dev)
{
	struct intel_iommu *iommu;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	if (!iommu)
		return -ENODEV;

	if (!dev_is_pci(dev))
		return device_context_mapped(iommu, bus, devfn);

	return !pci_for_each_dma_alias(to_pci_dev(dev),
				       domain_context_mapped_cb, iommu);
}