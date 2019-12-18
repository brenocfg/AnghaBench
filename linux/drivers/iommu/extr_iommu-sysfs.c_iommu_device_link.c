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
struct iommu_device {TYPE_1__* dev; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct iommu_device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int sysfs_add_link_to_group (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysfs_create_link_nowarn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link_from_group (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int iommu_device_link(struct iommu_device *iommu, struct device *link)
{
	int ret;

	if (!iommu || IS_ERR(iommu))
		return -ENODEV;

	ret = sysfs_add_link_to_group(&iommu->dev->kobj, "devices",
				      &link->kobj, dev_name(link));
	if (ret)
		return ret;

	ret = sysfs_create_link_nowarn(&link->kobj, &iommu->dev->kobj, "iommu");
	if (ret)
		sysfs_remove_link_from_group(&iommu->dev->kobj, "devices",
					     dev_name(link));

	return ret;
}