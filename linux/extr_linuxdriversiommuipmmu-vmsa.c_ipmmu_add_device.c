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
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM ; 
 int /*<<< orphan*/  CONFIG_IOMMU_DMA ; 
 int ENODEV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int ipmmu_init_arm_mapping (struct device*) ; 
 int /*<<< orphan*/  to_ipmmu (struct device*) ; 

__attribute__((used)) static int ipmmu_add_device(struct device *dev)
{
	struct iommu_group *group;

	/*
	 * Only let through devices that have been verified in xlate()
	 */
	if (!to_ipmmu(dev))
		return -ENODEV;

	if (IS_ENABLED(CONFIG_ARM) && !IS_ENABLED(CONFIG_IOMMU_DMA))
		return ipmmu_init_arm_mapping(dev);

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);

	iommu_group_put(group);
	return 0;
}