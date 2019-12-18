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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct intel_iommu {int dummy; } ;
struct dmar_domain {int dummy; } ;
struct device_domain_info {struct dmar_domain* domain; struct intel_iommu* iommu; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BUS_NUM (int) ; 
 struct dmar_domain* alloc_domain (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  device_domain_lock ; 
 struct intel_iommu* device_to_iommu (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device_domain_info* dmar_search_domain_by_dev_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  domain_exit (struct dmar_domain*) ; 
 scalar_t__ domain_init (struct dmar_domain*,struct intel_iommu*,int) ; 
 int /*<<< orphan*/  get_last_alias ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_for_each_dma_alias (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct dmar_domain *find_or_alloc_domain(struct device *dev, int gaw)
{
	struct device_domain_info *info;
	struct dmar_domain *domain = NULL;
	struct intel_iommu *iommu;
	u16 dma_alias;
	unsigned long flags;
	u8 bus, devfn;

	iommu = device_to_iommu(dev, &bus, &devfn);
	if (!iommu)
		return NULL;

	if (dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);

		pci_for_each_dma_alias(pdev, get_last_alias, &dma_alias);

		spin_lock_irqsave(&device_domain_lock, flags);
		info = dmar_search_domain_by_dev_info(pci_domain_nr(pdev->bus),
						      PCI_BUS_NUM(dma_alias),
						      dma_alias & 0xff);
		if (info) {
			iommu = info->iommu;
			domain = info->domain;
		}
		spin_unlock_irqrestore(&device_domain_lock, flags);

		/* DMA alias already has a domain, use it */
		if (info)
			goto out;
	}

	/* Allocate and initialize new domain for the device */
	domain = alloc_domain(0);
	if (!domain)
		return NULL;
	if (domain_init(domain, iommu, gaw)) {
		domain_exit(domain);
		return NULL;
	}

out:
	return domain;
}