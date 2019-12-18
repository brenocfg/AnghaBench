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
struct zpci_dev {int /*<<< orphan*/  iommu_dev; } ;
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct zpci_dev* sysdata; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static int s390_iommu_add_device(struct device *dev)
{
	struct iommu_group *group = iommu_group_get_for_dev(dev);
	struct zpci_dev *zdev = to_pci_dev(dev)->sysdata;

	if (IS_ERR(group))
		return PTR_ERR(group);

	iommu_group_put(group);
	iommu_device_link(&zdev->iommu_dev, dev);

	return 0;
}