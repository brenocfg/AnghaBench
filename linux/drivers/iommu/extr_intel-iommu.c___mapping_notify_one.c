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
struct intel_iommu {int /*<<< orphan*/  cap; } ;
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 scalar_t__ cap_caching_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_flush_iotlb_psi (struct intel_iommu*,struct dmar_domain*,unsigned long,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iommu_flush_write_buffer (struct intel_iommu*) ; 

__attribute__((used)) static inline void __mapping_notify_one(struct intel_iommu *iommu,
					struct dmar_domain *domain,
					unsigned long pfn, unsigned int pages)
{
	/* It's a non-present to present mapping. Only flush if caching mode */
	if (cap_caching_mode(iommu->cap))
		iommu_flush_iotlb_psi(iommu, domain, pfn, pages, 0, 1);
	else
		iommu_flush_write_buffer(iommu);
}