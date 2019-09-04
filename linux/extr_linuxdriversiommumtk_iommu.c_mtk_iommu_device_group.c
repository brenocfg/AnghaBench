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
struct mtk_iommu_data {struct iommu_group* m4u_group; } ;
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct iommu_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct iommu_group* iommu_group_alloc () ; 
 int /*<<< orphan*/  iommu_group_ref_get (struct iommu_group*) ; 
 struct mtk_iommu_data* mtk_iommu_get_m4u_data () ; 

__attribute__((used)) static struct iommu_group *mtk_iommu_device_group(struct device *dev)
{
	struct mtk_iommu_data *data = mtk_iommu_get_m4u_data();

	if (!data)
		return ERR_PTR(-ENODEV);

	/* All the client devices are in the same m4u iommu-group */
	if (!data->m4u_group) {
		data->m4u_group = iommu_group_alloc();
		if (IS_ERR(data->m4u_group))
			dev_err(dev, "Failed to allocate M4U IOMMU group\n");
	} else {
		iommu_group_ref_get(data->m4u_group);
	}
	return data->m4u_group;
}