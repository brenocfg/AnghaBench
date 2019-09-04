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

__attribute__((used)) static inline void pgste_set_key(pte_t *ptep, pgste_t pgste, pte_t entry,
				 struct mm_struct *mm)
{
#ifdef CONFIG_PGSTE
	unsigned long address;
	unsigned long nkey;

	if (!mm_uses_skeys(mm) || pte_val(entry) & _PAGE_INVALID)
		return;
	VM_BUG_ON(!(pte_val(*ptep) & _PAGE_INVALID));
	address = pte_val(entry) & PAGE_MASK;
	/*
	 * Set page access key and fetch protection bit from pgste.
	 * The guest C/R information is still in the PGSTE, set real
	 * key C/R to 0.
	 */
	nkey = (pgste_val(pgste) & (PGSTE_ACC_BITS | PGSTE_FP_BIT)) >> 56;
	nkey |= (pgste_val(pgste) & (PGSTE_GR_BIT | PGSTE_GC_BIT)) >> 48;
	page_set_storage_key(address, nkey, 0);
#endif
}