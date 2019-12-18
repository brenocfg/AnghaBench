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
 struct device* fsl_mc_cont_dev (struct device*) ; 
 struct iommu_group* iommu_group_alloc () ; 
 struct iommu_group* iommu_group_get (struct device*) ; 

struct iommu_group *fsl_mc_device_group(struct device *dev)
{
	struct device *cont_dev = fsl_mc_cont_dev(dev);
	struct iommu_group *group;

	group = iommu_group_get(cont_dev);
	if (!group)
		group = iommu_group_alloc();
	return group;
}