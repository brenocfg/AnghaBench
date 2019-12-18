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
struct iommu_sva_ops {int dummy; } ;
struct iommu_sva {struct iommu_sva_ops const* ops; } ;

/* Variables and functions */
 int EEXIST ; 

int iommu_sva_set_ops(struct iommu_sva *handle,
		      const struct iommu_sva_ops *sva_ops)
{
	if (handle->ops && handle->ops != sva_ops)
		return -EEXIST;

	handle->ops = sva_ops;
	return 0;
}