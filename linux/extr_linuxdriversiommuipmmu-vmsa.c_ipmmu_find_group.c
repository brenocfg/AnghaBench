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
struct ipmmu_vmsa_device {struct iommu_group* group; } ;
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct iommu_group*) ; 
 struct iommu_group* iommu_group_alloc () ; 
 struct iommu_group* iommu_group_ref_get (struct iommu_group*) ; 
 struct ipmmu_vmsa_device* to_ipmmu (struct device*) ; 

__attribute__((used)) static struct iommu_group *ipmmu_find_group(struct device *dev)
{
	struct ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	struct iommu_group *group;

	if (mmu->group)
		return iommu_group_ref_get(mmu->group);

	group = iommu_group_alloc();
	if (!IS_ERR(group))
		mmu->group = group;

	return group;
}