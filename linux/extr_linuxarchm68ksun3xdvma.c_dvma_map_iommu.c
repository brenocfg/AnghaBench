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

/* Variables and functions */
 int DVMA_PAGE_MASK ; 
 unsigned long DVMA_PAGE_SHIFT ; 
 scalar_t__ DVMA_PAGE_SIZE ; 
 int /*<<< orphan*/  IOMMU_FULL_BLOCK ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 int /*<<< orphan*/  dvma_entry_set (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iommu_pte ; 

inline int dvma_map_iommu(unsigned long kaddr, unsigned long baddr,
				 int len)
{
	unsigned long end, index;

	index = baddr >> DVMA_PAGE_SHIFT;
	end = ((baddr+len) >> DVMA_PAGE_SHIFT);

	if(len & ~DVMA_PAGE_MASK)
		end++;

	for(; index < end ; index++) {
//		if(dvma_entry_use(index))
//			BUG();
//		pr_info("mapping pa %lx to ba %lx\n", __pa(kaddr),
//			index << DVMA_PAGE_SHIFT);

		dvma_entry_set(index, __pa(kaddr));

		iommu_pte[index] |= IOMMU_FULL_BLOCK;
//		dvma_entry_inc(index);

		kaddr += DVMA_PAGE_SIZE;
	}

#ifdef DEBUG
	for(index = (baddr >> DVMA_PAGE_SHIFT); index < end; index++)
		dvma_print(index << DVMA_PAGE_SHIFT);
#endif
	return 0;

}