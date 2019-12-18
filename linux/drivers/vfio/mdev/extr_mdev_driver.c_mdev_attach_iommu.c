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
struct mdev_device {int /*<<< orphan*/  dev; } ;
struct iommu_group {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int iommu_group_add_device (struct iommu_group*,int /*<<< orphan*/ *) ; 
 struct iommu_group* iommu_group_alloc () ; 
 int /*<<< orphan*/  iommu_group_id (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 

__attribute__((used)) static int mdev_attach_iommu(struct mdev_device *mdev)
{
	int ret;
	struct iommu_group *group;

	group = iommu_group_alloc();
	if (IS_ERR(group))
		return PTR_ERR(group);

	ret = iommu_group_add_device(group, &mdev->dev);
	if (!ret)
		dev_info(&mdev->dev, "MDEV: group_id = %d\n",
			 iommu_group_id(group));

	iommu_group_put(group);
	return ret;
}