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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgste_t ;

/* Variables and functions */

__attribute__((used)) static inline pgste_t pgste_set_pte(pte_t *ptep, pgste_t pgste, pte_t entry)
{
#ifdef CONFIG_PGSTE
	if ((pte_val(entry) & _PAGE_PRESENT) &&
	    (pte_val(entry) & _PAGE_WRITE) &&
	    !(pte_val(entry) & _PAGE_INVALID)) {
		if (!MACHINE_HAS_ESOP) {
			/*
			 * Without enhanced suppression-on-protection force
			 * the dirty bit on for all writable ptes.
			 */
			pte_val(entry) |= _PAGE_DIRTY;
			pte_val(entry) &= ~_PAGE_PROTECT;
		}
		if (!(pte_val(entry) & _PAGE_PROTECT))
			/* This pte allows write access, set user-dirty */
			pgste_val(pgste) |= PGSTE_UC_BIT;
	}
#endif
	*ptep = entry;
	return pgste;
}