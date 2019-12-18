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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct pasid_entry {int dummy; } ;
struct intel_iommu {int /*<<< orphan*/  cap; int /*<<< orphan*/  ecap; int /*<<< orphan*/  agaw; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int EINVAL ; 
 int PASID_FLAG_SUPERVISOR_MODE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  X86_FEATURE_LA57 ; 
 scalar_t__ __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ cap_caching_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clflush_cache_range (struct pasid_entry*,int) ; 
 scalar_t__ cpu_feature_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_coherent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_flts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_smpwc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_srs (int /*<<< orphan*/ ) ; 
 struct pasid_entry* intel_pasid_get_entry (struct device*,int) ; 
 int /*<<< orphan*/  iommu_flush_write_buffer (struct intel_iommu*) ; 
 int /*<<< orphan*/  iotlb_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_cache_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_clear_entry (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_address_width (struct pasid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_set_domain_id (struct pasid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_set_flpm (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  pasid_set_flptr (struct pasid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_set_page_snoop (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  pasid_set_present (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_sre (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_translation_type (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int intel_pasid_setup_first_level(struct intel_iommu *iommu,
				  struct device *dev, pgd_t *pgd,
				  int pasid, u16 did, int flags)
{
	struct pasid_entry *pte;

	if (!ecap_flts(iommu->ecap)) {
		pr_err("No first level translation support on %s\n",
		       iommu->name);
		return -EINVAL;
	}

	pte = intel_pasid_get_entry(dev, pasid);
	if (WARN_ON(!pte))
		return -EINVAL;

	pasid_clear_entry(pte);

	/* Setup the first level page table pointer: */
	pasid_set_flptr(pte, (u64)__pa(pgd));
	if (flags & PASID_FLAG_SUPERVISOR_MODE) {
		if (!ecap_srs(iommu->ecap)) {
			pr_err("No supervisor request support on %s\n",
			       iommu->name);
			return -EINVAL;
		}
		pasid_set_sre(pte);
	}

#ifdef CONFIG_X86
	if (cpu_feature_enabled(X86_FEATURE_LA57))
		pasid_set_flpm(pte, 1);
#endif /* CONFIG_X86 */

	pasid_set_domain_id(pte, did);
	pasid_set_address_width(pte, iommu->agaw);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	/* Setup Present and PASID Granular Transfer Type: */
	pasid_set_translation_type(pte, 1);
	pasid_set_present(pte);

	if (!ecap_coherent(iommu->ecap))
		clflush_cache_range(pte, sizeof(*pte));

	if (cap_caching_mode(iommu->cap)) {
		pasid_cache_invalidation_with_pasid(iommu, did, pasid);
		iotlb_invalidation_with_pasid(iommu, did, pasid);
	} else {
		iommu_flush_write_buffer(iommu);
	}

	return 0;
}