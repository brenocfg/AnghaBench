#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iommu_sva {TYPE_2__* dev; } ;
struct iommu_ops {int (* sva_get_pasid ) (struct iommu_sva*) ;} ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int IOMMU_PASID_INVALID ; 
 int stub1 (struct iommu_sva*) ; 

int iommu_sva_get_pasid(struct iommu_sva *handle)
{
	const struct iommu_ops *ops = handle->dev->bus->iommu_ops;

	if (!ops || !ops->sva_get_pasid)
		return IOMMU_PASID_INVALID;

	return ops->sva_get_pasid(handle);
}