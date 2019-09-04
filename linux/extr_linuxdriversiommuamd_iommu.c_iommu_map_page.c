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
typedef  int u64 ;
struct protection_domain {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IOMMU_PROT_IR ; 
 int IOMMU_PROT_IW ; 
 int IOMMU_PROT_MASK ; 
 int IOMMU_PTE_FC ; 
 int IOMMU_PTE_IR ; 
 int IOMMU_PTE_IW ; 
 int IOMMU_PTE_PR ; 
 scalar_t__ IOMMU_PTE_PRESENT (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 int PAGE_SIZE_PTE (int,unsigned long) ; 
 int PAGE_SIZE_PTE_COUNT (unsigned long) ; 
 int PM_LEVEL_ENC (int) ; 
 int __sme_set (unsigned long) ; 
 int* alloc_pte (struct protection_domain*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_domain (struct protection_domain*) ; 

__attribute__((used)) static int iommu_map_page(struct protection_domain *dom,
			  unsigned long bus_addr,
			  unsigned long phys_addr,
			  unsigned long page_size,
			  int prot,
			  gfp_t gfp)
{
	u64 __pte, *pte;
	int i, count;

	BUG_ON(!IS_ALIGNED(bus_addr, page_size));
	BUG_ON(!IS_ALIGNED(phys_addr, page_size));

	if (!(prot & IOMMU_PROT_MASK))
		return -EINVAL;

	count = PAGE_SIZE_PTE_COUNT(page_size);
	pte   = alloc_pte(dom, bus_addr, page_size, NULL, gfp);

	if (!pte)
		return -ENOMEM;

	for (i = 0; i < count; ++i)
		if (IOMMU_PTE_PRESENT(pte[i]))
			return -EBUSY;

	if (count > 1) {
		__pte = PAGE_SIZE_PTE(__sme_set(phys_addr), page_size);
		__pte |= PM_LEVEL_ENC(7) | IOMMU_PTE_PR | IOMMU_PTE_FC;
	} else
		__pte = __sme_set(phys_addr) | IOMMU_PTE_PR | IOMMU_PTE_FC;

	if (prot & IOMMU_PROT_IR)
		__pte |= IOMMU_PTE_IR;
	if (prot & IOMMU_PROT_IW)
		__pte |= IOMMU_PTE_IW;

	for (i = 0; i < count; ++i)
		pte[i] = __pte;

	update_domain(dom);

	return 0;
}