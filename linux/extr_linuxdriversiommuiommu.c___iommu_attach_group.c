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
struct iommu_group {struct iommu_domain* domain; struct iommu_domain* default_domain; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __iommu_group_for_each_dev (struct iommu_group*,struct iommu_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_do_attach_device ; 

__attribute__((used)) static int __iommu_attach_group(struct iommu_domain *domain,
				struct iommu_group *group)
{
	int ret;

	if (group->default_domain && group->domain != group->default_domain)
		return -EBUSY;

	ret = __iommu_group_for_each_dev(group, domain,
					 iommu_group_do_attach_device);
	if (ret == 0)
		group->domain = domain;

	return ret;
}