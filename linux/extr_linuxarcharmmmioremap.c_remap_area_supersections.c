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
struct mem_type {unsigned long prot_sect; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long PMD_SECT_SUPER ; 
 scalar_t__ PMD_SIZE ; 
 int SUPERSECTION_SIZE ; 
 unsigned long __pfn_to_phys (unsigned long) ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 int /*<<< orphan*/  flush_pmd_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unmap_area_sections (unsigned long,size_t) ; 

__attribute__((used)) static int
remap_area_supersections(unsigned long virt, unsigned long pfn,
			 size_t size, const struct mem_type *type)
{
	unsigned long addr = virt, end = virt + size;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;

	/*
	 * Remove and free any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);

	pgd = pgd_offset_k(virt);
	pud = pud_offset(pgd, addr);
	pmd = pmd_offset(pud, addr);
	do {
		unsigned long super_pmd_val, i;

		super_pmd_val = __pfn_to_phys(pfn) | type->prot_sect |
				PMD_SECT_SUPER;
		super_pmd_val |= ((pfn >> (32 - PAGE_SHIFT)) & 0xf) << 20;

		for (i = 0; i < 8; i++) {
			pmd[0] = __pmd(super_pmd_val);
			pmd[1] = __pmd(super_pmd_val);
			flush_pmd_entry(pmd);

			addr += PMD_SIZE;
			pmd += 2;
		}

		pfn += SUPERSECTION_SIZE >> PAGE_SHIFT;
	} while (addr < end);

	return 0;
}