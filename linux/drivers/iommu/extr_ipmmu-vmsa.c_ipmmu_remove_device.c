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
struct ipmmu_vmsa_device {int /*<<< orphan*/  iommu; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_iommu_detach_device (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 struct ipmmu_vmsa_device* to_ipmmu (struct device*) ; 

__attribute__((used)) static void ipmmu_remove_device(struct device *dev)
{
	struct ipmmu_vmsa_device *mmu = to_ipmmu(dev);

	iommu_device_unlink(&mmu->iommu, dev);
	arm_iommu_detach_device(dev);
	iommu_group_remove_device(dev);
}