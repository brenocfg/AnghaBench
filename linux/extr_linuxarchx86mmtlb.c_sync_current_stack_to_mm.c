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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned long current_stack_pointer ; 
 int /*<<< orphan*/  p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 scalar_t__ pgtable_l5_enabled () ; 
 int /*<<< orphan*/  set_p4d (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_current_stack_to_mm(struct mm_struct *mm)
{
	unsigned long sp = current_stack_pointer;
	pgd_t *pgd = pgd_offset(mm, sp);

	if (pgtable_l5_enabled()) {
		if (unlikely(pgd_none(*pgd))) {
			pgd_t *pgd_ref = pgd_offset_k(sp);

			set_pgd(pgd, *pgd_ref);
		}
	} else {
		/*
		 * "pgd" is faked.  The top level entries are "p4d"s, so sync
		 * the p4d.  This compiles to approximately the same code as
		 * the 5-level case.
		 */
		p4d_t *p4d = p4d_offset(pgd, sp);

		if (unlikely(p4d_none(*p4d))) {
			pgd_t *pgd_ref = pgd_offset_k(sp);
			p4d_t *p4d_ref = p4d_offset(pgd_ref, sp);

			set_p4d(p4d, *p4d_ref);
		}
	}
}