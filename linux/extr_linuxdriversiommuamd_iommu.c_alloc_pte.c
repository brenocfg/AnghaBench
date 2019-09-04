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
typedef  scalar_t__ u64 ;
struct protection_domain {int mode; scalar_t__* pt_root; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__* IOMMU_PTE_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  IOMMU_PTE_PRESENT (scalar_t__) ; 
 unsigned long PAGE_SIZE_ALIGN (unsigned long,unsigned long) ; 
 int PAGE_SIZE_LEVEL (unsigned long) ; 
 size_t PM_LEVEL_INDEX (int,unsigned long) ; 
 scalar_t__ PM_LEVEL_PDE (int,int /*<<< orphan*/ ) ; 
 unsigned long PM_LEVEL_SIZE (int) ; 
 int PM_PTE_LEVEL (scalar_t__) ; 
 scalar_t__ cmpxchg64 (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  increase_address_space (struct protection_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_virt_to_phys (scalar_t__*) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 

__attribute__((used)) static u64 *alloc_pte(struct protection_domain *domain,
		      unsigned long address,
		      unsigned long page_size,
		      u64 **pte_page,
		      gfp_t gfp)
{
	int level, end_lvl;
	u64 *pte, *page;

	BUG_ON(!is_power_of_2(page_size));

	while (address > PM_LEVEL_SIZE(domain->mode))
		increase_address_space(domain, gfp);

	level   = domain->mode - 1;
	pte     = &domain->pt_root[PM_LEVEL_INDEX(level, address)];
	address = PAGE_SIZE_ALIGN(address, page_size);
	end_lvl = PAGE_SIZE_LEVEL(page_size);

	while (level > end_lvl) {
		u64 __pte, __npte;

		__pte = *pte;

		if (!IOMMU_PTE_PRESENT(__pte)) {
			page = (u64 *)get_zeroed_page(gfp);
			if (!page)
				return NULL;

			__npte = PM_LEVEL_PDE(level, iommu_virt_to_phys(page));

			/* pte could have been changed somewhere. */
			if (cmpxchg64(pte, __pte, __npte) != __pte) {
				free_page((unsigned long)page);
				continue;
			}
		}

		/* No level skipping support yet */
		if (PM_PTE_LEVEL(*pte) != level)
			return NULL;

		level -= 1;

		pte = IOMMU_PTE_PAGE(*pte);

		if (pte_page && level == end_lvl)
			*pte_page = pte;

		pte = &pte[PM_LEVEL_INDEX(level, address)];
	}

	return pte;
}