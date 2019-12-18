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
struct intel_iommu {int agaw; size_t seq_id; int /*<<< orphan*/  cap; int /*<<< orphan*/  ecap; int /*<<< orphan*/  name; } ;
struct dmar_domain {int agaw; int /*<<< orphan*/ * iommu_did; struct dma_pte* pgd; } ;
struct dma_pte {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ cap_caching_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clflush_cache_range (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_pte_addr (struct dma_pte*) ; 
 int /*<<< orphan*/  dma_pte_present (struct dma_pte*) ; 
 int /*<<< orphan*/  ecap_coherent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_slts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_smpwc (int /*<<< orphan*/ ) ; 
 struct pasid_entry* intel_pasid_get_entry (struct device*,int) ; 
 int /*<<< orphan*/  iommu_flush_write_buffer (struct intel_iommu*) ; 
 int /*<<< orphan*/  iotlb_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_cache_invalidation_with_pasid (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pasid_clear_entry (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_address_width (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  pasid_set_domain_id (struct pasid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_set_fault_enable (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_page_snoop (struct pasid_entry*,int) ; 
 int /*<<< orphan*/  pasid_set_present (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_slptr (struct pasid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_set_sre (struct pasid_entry*) ; 
 int /*<<< orphan*/  pasid_set_translation_type (struct pasid_entry*,int) ; 
 struct dma_pte* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct dma_pte*) ; 

int intel_pasid_setup_second_level(struct intel_iommu *iommu,
				   struct dmar_domain *domain,
				   struct device *dev, int pasid)
{
	struct pasid_entry *pte;
	struct dma_pte *pgd;
	u64 pgd_val;
	int agaw;
	u16 did;

	/*
	 * If hardware advertises no support for second level
	 * translation, return directly.
	 */
	if (!ecap_slts(iommu->ecap)) {
		pr_err("No second level translation support on %s\n",
		       iommu->name);
		return -EINVAL;
	}

	/*
	 * Skip top levels of page tables for iommu which has less agaw
	 * than default. Unnecessary for PT mode.
	 */
	pgd = domain->pgd;
	for (agaw = domain->agaw; agaw > iommu->agaw; agaw--) {
		pgd = phys_to_virt(dma_pte_addr(pgd));
		if (!dma_pte_present(pgd)) {
			dev_err(dev, "Invalid domain page table\n");
			return -EINVAL;
		}
	}

	pgd_val = virt_to_phys(pgd);
	did = domain->iommu_did[iommu->seq_id];

	pte = intel_pasid_get_entry(dev, pasid);
	if (!pte) {
		dev_err(dev, "Failed to get pasid entry of PASID %d\n", pasid);
		return -ENODEV;
	}

	pasid_clear_entry(pte);
	pasid_set_domain_id(pte, did);
	pasid_set_slptr(pte, pgd_val);
	pasid_set_address_width(pte, agaw);
	pasid_set_translation_type(pte, 2);
	pasid_set_fault_enable(pte);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	/*
	 * Since it is a second level only translation setup, we should
	 * set SRE bit as well (addresses are expected to be GPAs).
	 */
	pasid_set_sre(pte);
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