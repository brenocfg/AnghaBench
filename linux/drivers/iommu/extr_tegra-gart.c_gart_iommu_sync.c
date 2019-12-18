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
 int /*<<< orphan*/  gart_iommu_sync_map (struct iommu_domain*) ; 

__attribute__((used)) static void gart_iommu_sync(struct iommu_domain *domain,
			    struct iommu_iotlb_gather *gather)
{
	gart_iommu_sync_map(domain);
}