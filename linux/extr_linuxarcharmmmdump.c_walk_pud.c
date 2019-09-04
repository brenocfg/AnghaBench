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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned int PTRS_PER_PUD ; 
 unsigned int PUD_SIZE ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pmd (struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pud(struct pg_state *st, pgd_t *pgd, unsigned long start)
{
	pud_t *pud = pud_offset(pgd, 0);
	unsigned long addr;
	unsigned i;

	for (i = 0; i < PTRS_PER_PUD; i++, pud++) {
		addr = start + i * PUD_SIZE;
		if (!pud_none(*pud)) {
			walk_pmd(st, pud, addr);
		} else {
			note_page(st, addr, 2, pud_val(*pud), NULL);
		}
	}
}