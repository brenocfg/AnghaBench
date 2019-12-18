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
struct TYPE_2__ {int enabled; } ;
struct iommu_dev_data {int /*<<< orphan*/  lock; TYPE_1__ ats; scalar_t__ iommu_v2; struct protection_domain* domain; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PD_IOMMUV2_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  do_detach (struct iommu_dev_data*) ; 
 struct iommu_dev_data* get_dev_data (struct device*) ; 
 int /*<<< orphan*/  pci_disable_ats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdev_iommuv2_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static void detach_device(struct device *dev)
{
	struct protection_domain *domain;
	struct iommu_dev_data *dev_data;
	unsigned long flags;

	dev_data = get_dev_data(dev);
	domain   = dev_data->domain;

	spin_lock_irqsave(&domain->lock, flags);

	spin_lock(&dev_data->lock);

	/*
	 * First check if the device is still attached. It might already
	 * be detached from its domain because the generic
	 * iommu_detach_group code detached it and we try again here in
	 * our alias handling.
	 */
	if (WARN_ON(!dev_data->domain))
		goto out;

	do_detach(dev_data);

	if (!dev_is_pci(dev))
		goto out;

	if (domain->flags & PD_IOMMUV2_MASK && dev_data->iommu_v2)
		pdev_iommuv2_disable(to_pci_dev(dev));
	else if (dev_data->ats.enabled)
		pci_disable_ats(to_pci_dev(dev));

	dev_data->ats.enabled = false;

out:
	spin_unlock(&dev_data->lock);

	spin_unlock_irqrestore(&domain->lock, flags);
}