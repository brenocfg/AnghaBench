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

__attribute__((used)) static inline pgste_t pgste_update_all(pte_t pte, pgste_t pgste,
				       struct mm_struct *mm)
{
#ifdef CONFIG_PGSTE
	unsigned long address, bits, skey;

	if (!mm_uses_skeys(mm) || pte_val(pte) & _PAGE_INVALID)
		return pgste;
	address = pte_val(pte) & PAGE_MASK;
	skey = (unsigned long) page_get_storage_key(address);
	bits = skey & (_PAGE_CHANGED | _PAGE_REFERENCED);
	/* Transfer page changed & referenced bit to guest bits in pgste */
	pgste_val(pgste) |= bits << 48;		/* GR bit & GC bit */
	/* Copy page access key and fetch protection bit to pgste */
	pgste_val(pgste) &= ~(PGSTE_ACC_BITS | PGSTE_FP_BIT);
	pgste_val(pgste) |= (skey & (_PAGE_ACC_BITS | _PAGE_FP_BIT)) << 56;
#endif
	return pgste;

}