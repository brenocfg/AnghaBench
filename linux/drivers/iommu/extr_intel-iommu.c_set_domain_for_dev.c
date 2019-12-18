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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct intel_iommu {int dummy; } ;
struct dmar_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PCI_BUS_NUM (int) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 struct intel_iommu* device_to_iommu (struct device*,int*,int*) ; 
 struct dmar_domain* dmar_insert_one_dev_info (struct intel_iommu*,int,int,struct device*,struct dmar_domain*) ; 
 int /*<<< orphan*/  get_last_alias ; 
 int /*<<< orphan*/  pci_for_each_dma_alias (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct dmar_domain *set_domain_for_dev(struct device *dev,
					      struct dmar_domain *domain)
{
	struct intel_iommu *iommu;
	struct dmar_domain *tmp;
	u16 req_id, dma_alias;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	if (!iommu)
		return NULL;

	req_id = ((u16)bus << 8) | devfn;

	if (dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);

		pci_for_each_dma_alias(pdev, get_last_alias, &dma_alias);

		/* register PCI DMA alias device */
		if (req_id != dma_alias) {
			tmp = dmar_insert_one_dev_info(iommu, PCI_BUS_NUM(dma_alias),
					dma_alias & 0xff, NULL, domain);

			if (!tmp || tmp != domain)
				return tmp;
		}
	}

	tmp = dmar_insert_one_dev_info(iommu, bus, devfn, dev, domain);
	if (!tmp || tmp != domain)
		return tmp;

	return domain;
}