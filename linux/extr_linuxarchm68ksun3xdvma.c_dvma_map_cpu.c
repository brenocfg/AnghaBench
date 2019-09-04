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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long PGDIR_MASK ; 
 int PGDIR_SIZE ; 
 unsigned long PMD_MASK ; 
 int PMD_SIZE ; 
 unsigned long __pa (unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_pfn (unsigned long) ; 

inline int dvma_map_cpu(unsigned long kaddr,
			       unsigned long vaddr, int len)
{
	pgd_t *pgd;
	unsigned long end;
	int ret = 0;

	kaddr &= PAGE_MASK;
	vaddr &= PAGE_MASK;

	end = PAGE_ALIGN(vaddr + len);

	pr_debug("dvma: mapping kern %08lx to virt %08lx\n", kaddr, vaddr);
	pgd = pgd_offset_k(vaddr);

	do {
		pmd_t *pmd;
		unsigned long end2;

		if((pmd = pmd_alloc(&init_mm, pgd, vaddr)) == NULL) {
			ret = -ENOMEM;
			goto out;
		}

		if((end & PGDIR_MASK) > (vaddr & PGDIR_MASK))
			end2 = (vaddr + (PGDIR_SIZE-1)) & PGDIR_MASK;
		else
			end2 = end;

		do {
			pte_t *pte;
			unsigned long end3;

			if((pte = pte_alloc_kernel(pmd, vaddr)) == NULL) {
				ret = -ENOMEM;
				goto out;
			}

			if((end2 & PMD_MASK) > (vaddr & PMD_MASK))
				end3 = (vaddr + (PMD_SIZE-1)) & PMD_MASK;
			else
				end3 = end2;

			do {
				pr_debug("mapping %08lx phys to %08lx\n",
					 __pa(kaddr), vaddr);
				set_pte(pte, pfn_pte(virt_to_pfn(kaddr),
						     PAGE_KERNEL));
				pte++;
				kaddr += PAGE_SIZE;
				vaddr += PAGE_SIZE;
			} while(vaddr < end3);

		} while(vaddr < end2);

	} while(vaddr < end);

	flush_tlb_all();

 out:
	return ret;
}