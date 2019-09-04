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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 TYPE_1__* gart_handle ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 

__attribute__((used)) static void gart_iommu_remove_device(struct device *dev)
{
	iommu_group_remove_device(dev);
	iommu_device_unlink(&gart_handle->iommu, dev);
}