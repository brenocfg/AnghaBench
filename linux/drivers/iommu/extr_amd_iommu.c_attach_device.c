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
struct protection_domain {int flags; int /*<<< orphan*/  lock; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int enabled; void* qdep; } ;
struct iommu_dev_data {int /*<<< orphan*/  lock; TYPE_1__ ats; int /*<<< orphan*/  pri_tlp; scalar_t__ iommu_v2; int /*<<< orphan*/  passthrough; int /*<<< orphan*/ * domain; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int PD_IOMMUV2_MASK ; 
 scalar_t__ amd_iommu_iotlb_sup ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  do_attach (struct iommu_dev_data*,struct protection_domain*) ; 
 int /*<<< orphan*/  domain_flush_complete (struct protection_domain*) ; 
 int /*<<< orphan*/  domain_flush_tlb_pde (struct protection_domain*) ; 
 struct iommu_dev_data* get_dev_data (struct device*) ; 
 void* pci_ats_queue_depth (struct pci_dev*) ; 
 scalar_t__ pci_enable_ats (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_prg_resp_pasid_required (struct pci_dev*) ; 
 scalar_t__ pdev_iommuv2_enable (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int attach_device(struct device *dev,
			 struct protection_domain *domain)
{
	struct pci_dev *pdev;
	struct iommu_dev_data *dev_data;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&domain->lock, flags);

	dev_data = get_dev_data(dev);

	spin_lock(&dev_data->lock);

	ret = -EBUSY;
	if (dev_data->domain != NULL)
		goto out;

	if (!dev_is_pci(dev))
		goto skip_ats_check;

	pdev = to_pci_dev(dev);
	if (domain->flags & PD_IOMMUV2_MASK) {
		ret = -EINVAL;
		if (!dev_data->passthrough)
			goto out;

		if (dev_data->iommu_v2) {
			if (pdev_iommuv2_enable(pdev) != 0)
				goto out;

			dev_data->ats.enabled = true;
			dev_data->ats.qdep    = pci_ats_queue_depth(pdev);
			dev_data->pri_tlp     = pci_prg_resp_pasid_required(pdev);
		}
	} else if (amd_iommu_iotlb_sup &&
		   pci_enable_ats(pdev, PAGE_SHIFT) == 0) {
		dev_data->ats.enabled = true;
		dev_data->ats.qdep    = pci_ats_queue_depth(pdev);
	}

skip_ats_check:
	ret = 0;

	do_attach(dev_data, domain);

	/*
	 * We might boot into a crash-kernel here. The crashed kernel
	 * left the caches in the IOMMU dirty. So we have to flush
	 * here to evict all dirty stuff.
	 */
	domain_flush_tlb_pde(domain);

	domain_flush_complete(domain);

out:
	spin_unlock(&dev_data->lock);

	spin_unlock_irqrestore(&domain->lock, flags);

	return ret;
}