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
struct seq_file {int dummy; } ;
struct pg_state {unsigned long current_address; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PMD_SIZE ; 
 int PTRS_PER_PMD ; 
 unsigned int _PAGE_INVALID ; 
 unsigned int _SEGMENT_ENTRY_NOEXEC ; 
 unsigned int _SEGMENT_ENTRY_PROTECT ; 
 unsigned long max_addr ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,unsigned int,int) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pte_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pmd_level(struct seq_file *m, struct pg_state *st,
			   pud_t *pud, unsigned long addr)
{
	unsigned int prot;
	pmd_t *pmd;
	int i;

	for (i = 0; i < PTRS_PER_PMD && addr < max_addr; i++) {
		st->current_address = addr;
		pmd = pmd_offset(pud, addr);
		if (!pmd_none(*pmd)) {
			if (pmd_large(*pmd)) {
				prot = pmd_val(*pmd) &
					(_SEGMENT_ENTRY_PROTECT |
					 _SEGMENT_ENTRY_NOEXEC);
				note_page(m, st, prot, 3);
			} else
				walk_pte_level(m, st, pmd, addr);
		} else
			note_page(m, st, _PAGE_INVALID, 3);
		addr += PMD_SIZE;
	}
}