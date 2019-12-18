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
struct zpci_dev {int /*<<< orphan*/  iommu_dev; scalar_t__ s390_domain; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct zpci_dev* sysdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  s390_iommu_detach_device (struct iommu_domain*,struct device*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static void s390_iommu_remove_device(struct device *dev)
{
	struct zpci_dev *zdev = to_pci_dev(dev)->sysdata;
	struct iommu_domain *domain;

	/*
	 * This is a workaround for a scenario where the IOMMU API common code
	 * "forgets" to call the detach_dev callback: After binding a device
	 * to vfio-pci and completing the VFIO_SET_IOMMU ioctl (which triggers
	 * the attach_dev), removing the device via
	 * "echo 1 > /sys/bus/pci/devices/.../remove" won't trigger detach_dev,
	 * only remove_device will be called via the BUS_NOTIFY_REMOVED_DEVICE
	 * notifier.
	 *
	 * So let's call detach_dev from here if it hasn't been called before.
	 */
	if (zdev && zdev->s390_domain) {
		domain = iommu_get_domain_for_dev(dev);
		if (domain)
			s390_iommu_detach_device(domain, dev);
	}

	iommu_device_unlink(&zdev->iommu_dev, dev);
	iommu_group_remove_device(dev);
}