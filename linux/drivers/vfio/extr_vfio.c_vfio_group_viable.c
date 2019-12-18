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
struct vfio_group {int /*<<< orphan*/  iommu_group; } ;

/* Variables and functions */
 scalar_t__ iommu_group_for_each_dev (int /*<<< orphan*/ ,struct vfio_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_dev_viable ; 

__attribute__((used)) static bool vfio_group_viable(struct vfio_group *group)
{
	return (iommu_group_for_each_dev(group->iommu_group,
					 group, vfio_dev_viable) == 0);
}