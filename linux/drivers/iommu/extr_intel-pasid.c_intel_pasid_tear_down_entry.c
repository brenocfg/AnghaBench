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
typedef  int /*<<< orphan*/  u16 ;
struct pasid_entry {int dummy; } ;
struct intel_iommu {int /*<<< orphan*/  cap; int /*<<< orphan*/  ecap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cap_caching_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clflush_cache_range (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  devtlb_invalidation_with_pasid (struct intel_iommu*,struct device*,int) ; 
 int /*<<< orphan*/  ecap_coherent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pasid_clear_entry (struct device*,int) ; 
 struct pasid_entry* intel_pasid_get_entry (struct device*,int) ; 
 int /*<<< orphan*/  iotlb_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_cache_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_get_domain_id (struct pasid_entry*) ; 

void intel_pasid_tear_down_entry(struct intel_iommu *iommu,
				 struct device *dev, int pasid)
{
	struct pasid_entry *pte;
	u16 did;

	pte = intel_pasid_get_entry(dev, pasid);
	if (WARN_ON(!pte))
		return;

	did = pasid_get_domain_id(pte);
	intel_pasid_clear_entry(dev, pasid);

	if (!ecap_coherent(iommu->ecap))
		clflush_cache_range(pte, sizeof(*pte));

	pasid_cache_invalidation_with_pasid(iommu, did, pasid);
	iotlb_invalidation_with_pasid(iommu, did, pasid);

	/* Device IOTLB doesn't need to be flushed in caching mode. */
	if (!cap_caching_mode(iommu->cap))
		devtlb_invalidation_with_pasid(iommu, dev, pasid);
}