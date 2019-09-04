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
 scalar_t__ IS_ERR (struct iommu_device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link_from_group (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void iommu_device_unlink(struct iommu_device *iommu, struct device *link)
{
	if (!iommu || IS_ERR(iommu))
		return;

	sysfs_remove_link(&link->kobj, "iommu");
	sysfs_remove_link_from_group(&iommu->dev->kobj, "devices", dev_name(link));
}