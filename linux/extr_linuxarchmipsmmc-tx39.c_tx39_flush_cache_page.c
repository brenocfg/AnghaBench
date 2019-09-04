#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int VM_EXEC ; 
 int _PAGE_PRESENT ; 
 int _PAGE_VALID ; 
 scalar_t__ cpu_context (int /*<<< orphan*/ ,struct mm_struct*) ; 
 scalar_t__ cpu_has_dc_aliases ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tx39_blast_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  tx39_blast_dcache_page_indexed (unsigned long) ; 
 int /*<<< orphan*/  tx39_blast_icache_page (unsigned long) ; 
 int /*<<< orphan*/  tx39_blast_icache_page_indexed (unsigned long) ; 

__attribute__((used)) static void tx39_flush_cache_page(struct vm_area_struct *vma, unsigned long page, unsigned long pfn)
{
	int exec = vma->vm_flags & VM_EXEC;
	struct mm_struct *mm = vma->vm_mm;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	/*
	 * If ownes no valid ASID yet, cannot possibly have gotten
	 * this page into the cache.
	 */
	if (cpu_context(smp_processor_id(), mm) == 0)
		return;

	page &= PAGE_MASK;
	pgdp = pgd_offset(mm, page);
	pudp = pud_offset(pgdp, page);
	pmdp = pmd_offset(pudp, page);
	ptep = pte_offset(pmdp, page);

	/*
	 * If the page isn't marked valid, the page cannot possibly be
	 * in the cache.
	 */
	if (!(pte_val(*ptep) & _PAGE_PRESENT))
		return;

	/*
	 * Doing flushes for another ASID than the current one is
	 * too difficult since stupid R4k caches do a TLB translation
	 * for every cache flush operation.  So we do indexed flushes
	 * in that case, which doesn't overly flush the cache too much.
	 */
	if ((mm == current->active_mm) && (pte_val(*ptep) & _PAGE_VALID)) {
		if (cpu_has_dc_aliases || exec)
			tx39_blast_dcache_page(page);
		if (exec)
			tx39_blast_icache_page(page);

		return;
	}

	/*
	 * Do indexed flush, too much work to get the (possible) TLB refills
	 * to work correctly.
	 */
	if (cpu_has_dc_aliases || exec)
		tx39_blast_dcache_page_indexed(page);
	if (exec)
		tx39_blast_icache_page_indexed(page);
}