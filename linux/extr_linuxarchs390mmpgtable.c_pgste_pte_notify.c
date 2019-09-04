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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgste_t ;

/* Variables and functions */

__attribute__((used)) static inline pgste_t pgste_pte_notify(struct mm_struct *mm,
				       unsigned long addr,
				       pte_t *ptep, pgste_t pgste)
{
#ifdef CONFIG_PGSTE
	unsigned long bits;

	bits = pgste_val(pgste) & (PGSTE_IN_BIT | PGSTE_VSIE_BIT);
	if (bits) {
		pgste_val(pgste) ^= bits;
		ptep_notify(mm, addr, ptep, bits);
	}
#endif
	return pgste;
}