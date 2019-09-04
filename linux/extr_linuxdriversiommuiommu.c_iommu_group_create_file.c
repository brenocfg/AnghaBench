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
struct iommu_group_attribute {int /*<<< orphan*/  attr; } ;
struct iommu_group {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iommu_group_create_file(struct iommu_group *group,
				   struct iommu_group_attribute *attr)
{
	return sysfs_create_file(&group->kobj, &attr->attr);
}