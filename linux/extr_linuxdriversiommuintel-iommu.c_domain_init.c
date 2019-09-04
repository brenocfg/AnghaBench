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
struct intel_iommu {int /*<<< orphan*/  node; int /*<<< orphan*/  cap; int /*<<< orphan*/  ecap; } ;
struct dmar_domain {int gaw; int agaw; int iommu_coherency; int iommu_snooping; struct dma_pte* pgd; int /*<<< orphan*/  nid; scalar_t__ iommu_superpage; int /*<<< orphan*/  iovad; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IOVA_START_PFN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VTD_PAGE_SIZE ; 
 int /*<<< orphan*/  __iommu_flush_cache (struct intel_iommu*,struct dma_pte*,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_pgtable_page (int /*<<< orphan*/ ) ; 
 int cap_mgaw (int /*<<< orphan*/ ) ; 
 unsigned long cap_sagaw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_super_page_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain_reserve_special_ranges (struct dmar_domain*) ; 
 scalar_t__ ecap_coherent (int /*<<< orphan*/ ) ; 
 scalar_t__ ecap_sc_support (int /*<<< orphan*/ ) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 scalar_t__ fls (int /*<<< orphan*/ ) ; 
 int guestwidth_to_adjustwidth (int) ; 
 int /*<<< orphan*/  init_iova_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_iova_flush_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_iommu_superpage ; 
 int /*<<< orphan*/  iommu_flush_iova ; 
 int /*<<< orphan*/  iova_entry_free ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 int width_to_agaw (int) ; 

__attribute__((used)) static int domain_init(struct dmar_domain *domain, struct intel_iommu *iommu,
		       int guest_width)
{
	int adjust_width, agaw;
	unsigned long sagaw;
	int err;

	init_iova_domain(&domain->iovad, VTD_PAGE_SIZE, IOVA_START_PFN);

	err = init_iova_flush_queue(&domain->iovad,
				    iommu_flush_iova, iova_entry_free);
	if (err)
		return err;

	domain_reserve_special_ranges(domain);

	/* calculate AGAW */
	if (guest_width > cap_mgaw(iommu->cap))
		guest_width = cap_mgaw(iommu->cap);
	domain->gaw = guest_width;
	adjust_width = guestwidth_to_adjustwidth(guest_width);
	agaw = width_to_agaw(adjust_width);
	sagaw = cap_sagaw(iommu->cap);
	if (!test_bit(agaw, &sagaw)) {
		/* hardware doesn't support it, choose a bigger one */
		pr_debug("Hardware doesn't support agaw %d\n", agaw);
		agaw = find_next_bit(&sagaw, 5, agaw);
		if (agaw >= 5)
			return -ENODEV;
	}
	domain->agaw = agaw;

	if (ecap_coherent(iommu->ecap))
		domain->iommu_coherency = 1;
	else
		domain->iommu_coherency = 0;

	if (ecap_sc_support(iommu->ecap))
		domain->iommu_snooping = 1;
	else
		domain->iommu_snooping = 0;

	if (intel_iommu_superpage)
		domain->iommu_superpage = fls(cap_super_page_val(iommu->cap));
	else
		domain->iommu_superpage = 0;

	domain->nid = iommu->node;

	/* always allocate the top pgd */
	domain->pgd = (struct dma_pte *)alloc_pgtable_page(domain->nid);
	if (!domain->pgd)
		return -ENOMEM;
	__iommu_flush_cache(iommu, domain->pgd, PAGE_SIZE);
	return 0;
}