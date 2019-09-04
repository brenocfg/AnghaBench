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
 unsigned int PMD_SIZE ; 
 unsigned int PTRS_PER_PMD ; 
 unsigned int SECTION_SIZE ; 
 char* get_domain_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pte (struct pg_state*,int /*<<< orphan*/ *,unsigned long,char const*) ; 

__attribute__((used)) static void walk_pmd(struct pg_state *st, pud_t *pud, unsigned long start)
{
	pmd_t *pmd = pmd_offset(pud, 0);
	unsigned long addr;
	unsigned i;
	const char *domain;

	for (i = 0; i < PTRS_PER_PMD; i++, pmd++) {
		addr = start + i * PMD_SIZE;
		domain = get_domain_name(pmd);
		if (pmd_none(*pmd) || pmd_large(*pmd) || !pmd_present(*pmd))
			note_page(st, addr, 3, pmd_val(*pmd), domain);
		else
			walk_pte(st, pmd, addr, domain);

		if (SECTION_SIZE < PMD_SIZE && pmd_large(pmd[1])) {
			addr += SECTION_SIZE;
			pmd++;
			domain = get_domain_name(pmd);
			note_page(st, addr, 3, pmd_val(*pmd), domain);
		}
	}
}