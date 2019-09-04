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
struct pg_state {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int PMD_SIZE ; 
 unsigned int PTRS_PER_PMD ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_sect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pte (struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pmd(struct pg_state *st, pud_t *pudp, unsigned long start)
{
	pmd_t *pmdp = pmd_offset(pudp, 0UL);
	unsigned long addr;
	unsigned i;

	for (i = 0; i < PTRS_PER_PMD; i++, pmdp++) {
		pmd_t pmd = READ_ONCE(*pmdp);

		addr = start + i * PMD_SIZE;
		if (pmd_none(pmd) || pmd_sect(pmd)) {
			note_page(st, addr, 3, pmd_val(pmd));
		} else {
			BUG_ON(pmd_bad(pmd));
			walk_pte(st, pmdp, addr);
		}
	}
}