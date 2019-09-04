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
struct pg_state {unsigned long start_address; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PGDIR_SIZE ; 
 unsigned int PTRS_PER_PGD ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pud (struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pagetables(struct pg_state *st)
{
	pgd_t *pgd = pgd_offset_k(0UL);
	unsigned int i;
	unsigned long addr;

	addr = st->start_address;

	/*
	 * Traverse the linux pagetable structure and dump pages that are in
	 * the hash pagetable.
	 */
	for (i = 0; i < PTRS_PER_PGD; i++, pgd++, addr += PGDIR_SIZE) {
		if (!pgd_none(*pgd) && !pgd_huge(*pgd))
			/* pgd exists */
			walk_pud(st, pgd, addr);
		else
			note_page(st, addr, 1, pgd_val(*pgd));
	}
}