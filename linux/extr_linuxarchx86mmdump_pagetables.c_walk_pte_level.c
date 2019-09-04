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
struct pg_state {int /*<<< orphan*/  current_address; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprotval_t ;

/* Variables and functions */
 int PTE_LEVEL_MULT ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  effective_prot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_addr (unsigned long) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void walk_pte_level(struct seq_file *m, struct pg_state *st, pmd_t addr,
			   pgprotval_t eff_in, unsigned long P)
{
	int i;
	pte_t *pte;
	pgprotval_t prot, eff;

	for (i = 0; i < PTRS_PER_PTE; i++) {
		st->current_address = normalize_addr(P + i * PTE_LEVEL_MULT);
		pte = pte_offset_map(&addr, st->current_address);
		prot = pte_flags(*pte);
		eff = effective_prot(eff_in, prot);
		note_page(m, st, __pgprot(prot), eff, 5);
		pte_unmap(pte);
	}
}