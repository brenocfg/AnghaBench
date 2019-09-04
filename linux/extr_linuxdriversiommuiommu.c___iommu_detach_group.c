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
struct iommu_group {struct iommu_domain* default_domain; struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __iommu_group_for_each_dev (struct iommu_group*,struct iommu_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_do_attach_device ; 
 int /*<<< orphan*/  iommu_group_do_detach_device ; 

__attribute__((used)) static void __iommu_detach_group(struct iommu_domain *domain,
				 struct iommu_group *group)
{
	int ret;

	if (!group->default_domain) {
		__iommu_group_for_each_dev(group, domain,
					   iommu_group_do_detach_device);
		group->domain = NULL;
		return;
	}

	if (group->domain == group->default_domain)
		return;

	/* Detach by re-attaching to the default domain */
	ret = __iommu_group_for_each_dev(group, group->default_domain,
					 iommu_group_do_attach_device);
	if (ret != 0)
		WARN_ON(1);
	else
		group->domain = group->default_domain;
}