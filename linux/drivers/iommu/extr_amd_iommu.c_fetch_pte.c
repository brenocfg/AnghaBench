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
struct protection_domain {int mode; int /*<<< orphan*/ * pt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IOMMU_PTE_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_PTE_PRESENT (int /*<<< orphan*/ ) ; 
 int PAGE_MODE_7_LEVEL ; 
 size_t PM_LEVEL_INDEX (int,unsigned long) ; 
 unsigned long PM_LEVEL_SIZE (int) ; 
 int PM_PTE_LEVEL (int /*<<< orphan*/ ) ; 
 unsigned long PTE_LEVEL_PAGE_SIZE (int) ; 
 int /*<<< orphan*/ * first_pte_l7 (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 *fetch_pte(struct protection_domain *domain,
		      unsigned long address,
		      unsigned long *page_size)
{
	int level;
	u64 *pte;

	*page_size = 0;

	if (address > PM_LEVEL_SIZE(domain->mode))
		return NULL;

	level	   =  domain->mode - 1;
	pte	   = &domain->pt_root[PM_LEVEL_INDEX(level, address)];
	*page_size =  PTE_LEVEL_PAGE_SIZE(level);

	while (level > 0) {

		/* Not Present */
		if (!IOMMU_PTE_PRESENT(*pte))
			return NULL;

		/* Large PTE */
		if (PM_PTE_LEVEL(*pte) == 7 ||
		    PM_PTE_LEVEL(*pte) == 0)
			break;

		/* No level skipping support yet */
		if (PM_PTE_LEVEL(*pte) != level)
			return NULL;

		level -= 1;

		/* Walk to the next level */
		pte	   = IOMMU_PTE_PAGE(*pte);
		pte	   = &pte[PM_LEVEL_INDEX(level, address)];
		*page_size = PTE_LEVEL_PAGE_SIZE(level);
	}

	/*
	 * If we have a series of large PTEs, make
	 * sure to return a pointer to the first one.
	 */
	if (PM_PTE_LEVEL(*pte) == PAGE_MODE_7_LEVEL)
		pte = first_pte_l7(pte, page_size, NULL);

	return pte;
}