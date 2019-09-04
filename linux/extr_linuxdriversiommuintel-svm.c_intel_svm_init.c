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
struct pasid_state_entry {int dummy; } ;
struct pasid_entry {int dummy; } ;
struct page {int dummy; } ;
struct intel_iommu {int pasid_max; int /*<<< orphan*/  name; int /*<<< orphan*/  pasid_state_table; int /*<<< orphan*/  ecap; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  X86_FEATURE_GBPAGES ; 
 int /*<<< orphan*/  X86_FEATURE_LA57 ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int) ; 
 int /*<<< orphan*/  cap_5lp_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fl1gp_support (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_feature_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ ecap_dis (int /*<<< orphan*/ ) ; 
 int ecap_pss (int /*<<< orphan*/ ) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

int intel_svm_init(struct intel_iommu *iommu)
{
	struct page *pages;
	int order;

	if (cpu_feature_enabled(X86_FEATURE_GBPAGES) &&
			!cap_fl1gp_support(iommu->cap))
		return -EINVAL;

	if (cpu_feature_enabled(X86_FEATURE_LA57) &&
			!cap_5lp_support(iommu->cap))
		return -EINVAL;

	/* Start at 2 because it's defined as 2^(1+PSS) */
	iommu->pasid_max = 2 << ecap_pss(iommu->ecap);

	/* Eventually I'm promised we will get a multi-level PASID table
	 * and it won't have to be physically contiguous. Until then,
	 * limit the size because 8MiB contiguous allocations can be hard
	 * to come by. The limit of 0x20000, which is 1MiB for each of
	 * the PASID and PASID-state tables, is somewhat arbitrary. */
	if (iommu->pasid_max > 0x20000)
		iommu->pasid_max = 0x20000;

	order = get_order(sizeof(struct pasid_entry) * iommu->pasid_max);
	if (ecap_dis(iommu->ecap)) {
		/* Just making it explicit... */
		BUILD_BUG_ON(sizeof(struct pasid_entry) != sizeof(struct pasid_state_entry));
		pages = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
		if (pages)
			iommu->pasid_state_table = page_address(pages);
		else
			pr_warn("IOMMU: %s: Failed to allocate PASID state table\n",
				iommu->name);
	}

	return 0;
}