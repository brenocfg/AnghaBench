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
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 size_t __iommu_unmap (struct iommu_domain*,unsigned long,size_t,struct iommu_iotlb_gather*) ; 

size_t iommu_unmap_fast(struct iommu_domain *domain,
			unsigned long iova, size_t size,
			struct iommu_iotlb_gather *iotlb_gather)
{
	return __iommu_unmap(domain, iova, size, iotlb_gather);
}