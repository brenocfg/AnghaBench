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
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_COHERENT_ICACHE ; 
 int /*<<< orphan*/  CPU_FTR_NOEXECUTE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int _PAGE_HPTEFLAGS ; 
 int /*<<< orphan*/  __pte (int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_icache_page (struct page*) ; 
 struct page* maybe_pte_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_looks_normal (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t set_pte_filter(pte_t pte)
{
	if (radix_enabled())
		return pte;

	pte = __pte(pte_val(pte) & ~_PAGE_HPTEFLAGS);
	if (pte_looks_normal(pte) && !(cpu_has_feature(CPU_FTR_COHERENT_ICACHE) ||
				       cpu_has_feature(CPU_FTR_NOEXECUTE))) {
		struct page *pg = maybe_pte_to_page(pte);
		if (!pg)
			return pte;
		if (!test_bit(PG_arch_1, &pg->flags)) {
			flush_dcache_icache_page(pg);
			set_bit(PG_arch_1, &pg->flags);
		}
	}
	return pte;
}