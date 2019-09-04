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
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int /*<<< orphan*/  CONFIG_XPA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_SW (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int _PAGE_DIRTY ; 
 unsigned int _PAGE_VALID ; 
 int /*<<< orphan*/  cpu_has_64bits ; 
 int /*<<< orphan*/  uasm_i_lui (int /*<<< orphan*/ **,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_or (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_ori (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
iPTE_SW(u32 **p, struct uasm_reloc **r, unsigned int pte, unsigned int ptr,
	unsigned int mode, unsigned int scratch)
{
	unsigned int hwmode = mode & (_PAGE_VALID | _PAGE_DIRTY);
	unsigned int swmode = mode & ~hwmode;

	if (IS_ENABLED(CONFIG_XPA) && !cpu_has_64bits) {
		uasm_i_lui(p, scratch, swmode >> 16);
		uasm_i_or(p, pte, pte, scratch);
		BUG_ON(swmode & 0xffff);
	} else {
		uasm_i_ori(p, pte, pte, mode);
	}

#ifdef CONFIG_SMP
# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (cpu_has_64bits)
		uasm_i_scd(p, pte, 0, ptr);
	else
# endif
		UASM_i_SC(p, pte, 0, ptr);

	if (r10000_llsc_war())
		uasm_il_beqzl(p, r, pte, label_smp_pgtable_change);
	else
		uasm_il_beqz(p, r, pte, label_smp_pgtable_change);

# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (!cpu_has_64bits) {
		/* no uasm_i_nop needed */
		uasm_i_ll(p, pte, sizeof(pte_t) / 2, ptr);
		uasm_i_ori(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uasm_i_sc(p, pte, sizeof(pte_t) / 2, ptr);
		uasm_il_beqz(p, r, pte, label_smp_pgtable_change);
		/* no uasm_i_nop needed */
		uasm_i_lw(p, pte, 0, ptr);
	} else
		uasm_i_nop(p);
# else
	uasm_i_nop(p);
# endif
#else
# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (cpu_has_64bits)
		uasm_i_sd(p, pte, 0, ptr);
	else
# endif
		UASM_i_SW(p, pte, 0, ptr);

# ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (!cpu_has_64bits) {
		uasm_i_lw(p, pte, sizeof(pte_t) / 2, ptr);
		uasm_i_ori(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uasm_i_sw(p, pte, sizeof(pte_t) / 2, ptr);
		uasm_i_lw(p, pte, 0, ptr);
	}
# endif
#endif
}