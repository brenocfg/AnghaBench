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

/* Variables and functions */
 int GCR3_VALID ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_MASK ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int* iommu_phys_to_virt (int) ; 
 int iommu_virt_to_phys (int*) ; 

__attribute__((used)) static u64 *__get_gcr3_pte(u64 *root, int level, int pasid, bool alloc)
{
	int index;
	u64 *pte;

	while (true) {

		index = (pasid >> (9 * level)) & 0x1ff;
		pte   = &root[index];

		if (level == 0)
			break;

		if (!(*pte & GCR3_VALID)) {
			if (!alloc)
				return NULL;

			root = (void *)get_zeroed_page(GFP_ATOMIC);
			if (root == NULL)
				return NULL;

			*pte = iommu_virt_to_phys(root) | GCR3_VALID;
		}

		root = iommu_phys_to_virt(*pte & PAGE_MASK);

		level -= 1;
	}

	return pte;
}