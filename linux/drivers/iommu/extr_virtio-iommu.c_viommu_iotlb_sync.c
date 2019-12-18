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
struct viommu_domain {int /*<<< orphan*/  viommu; } ;
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 struct viommu_domain* to_viommu_domain (struct iommu_domain*) ; 
 int /*<<< orphan*/  viommu_sync_req (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viommu_iotlb_sync(struct iommu_domain *domain,
			      struct iommu_iotlb_gather *gather)
{
	struct viommu_domain *vdomain = to_viommu_domain(domain);

	viommu_sync_req(vdomain->viommu);
}