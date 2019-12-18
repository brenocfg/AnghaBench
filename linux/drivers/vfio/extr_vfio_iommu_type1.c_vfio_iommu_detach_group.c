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
struct vfio_group {int /*<<< orphan*/  iommu_group; scalar_t__ mdev_group; } ;
struct vfio_domain {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_detach_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_for_each_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_mdev_detach_domain ; 

__attribute__((used)) static void vfio_iommu_detach_group(struct vfio_domain *domain,
				    struct vfio_group *group)
{
	if (group->mdev_group)
		iommu_group_for_each_dev(group->iommu_group, domain->domain,
					 vfio_mdev_detach_domain);
	else
		iommu_detach_group(domain->domain, group->iommu_group);
}