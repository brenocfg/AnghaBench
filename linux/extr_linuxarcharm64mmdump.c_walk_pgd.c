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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int PGDIR_SIZE ; 
 unsigned int PTRS_PER_PGD ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pud (struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pgd(struct pg_state *st, struct mm_struct *mm,
		     unsigned long start)
{
	pgd_t *pgdp = pgd_offset(mm, 0UL);
	unsigned i;
	unsigned long addr;

	for (i = 0; i < PTRS_PER_PGD; i++, pgdp++) {
		pgd_t pgd = READ_ONCE(*pgdp);

		addr = start + i * PGDIR_SIZE;
		if (pgd_none(pgd)) {
			note_page(st, addr, 1, pgd_val(pgd));
		} else {
			BUG_ON(pgd_bad(pgd));
			walk_pud(st, pgdp, addr);
		}
	}
}