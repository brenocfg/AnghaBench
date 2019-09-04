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
struct platform_device {int dummy; } ;
struct ipmmu_vmsa_device {int /*<<< orphan*/  mapping; int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_iommu_release_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmmu_device_reset (struct ipmmu_vmsa_device*) ; 
 struct ipmmu_vmsa_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ipmmu_remove(struct platform_device *pdev)
{
	struct ipmmu_vmsa_device *mmu = platform_get_drvdata(pdev);

	iommu_device_sysfs_remove(&mmu->iommu);
	iommu_device_unregister(&mmu->iommu);

	arm_iommu_release_mapping(mmu->mapping);

	ipmmu_device_reset(mmu);

	return 0;
}