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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  C0_ENTRYLO0 ; 
 int /*<<< orphan*/  C0_ENTRYLO1 ; 
 int /*<<< orphan*/  C0_INDEX ; 
 int /*<<< orphan*/  CONFIG_XPA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_LW (int /*<<< orphan*/ **,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_MTC0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_ROTR (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PAGE_GLOBAL ; 
 int /*<<< orphan*/  build_convert_pte_to_entrylo (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  build_tlb_probe_entry (int /*<<< orphan*/ **) ; 
 scalar_t__ cpu_has_xpa ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_xpa_disabled ; 
 scalar_t__ r45k_bvahwbug () ; 
 scalar_t__ r4k_250MHZhwbug () ; 
 int /*<<< orphan*/  uasm_i_ext (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_mthc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 

void build_update_entries(u32 **p, unsigned int tmp, unsigned int ptep)
{
	int pte_off_even = 0;
	int pte_off_odd = sizeof(pte_t);

#if defined(CONFIG_CPU_MIPS32) && defined(CONFIG_PHYS_ADDR_T_64BIT)
	/* The low 32 bits of EntryLo is stored in pte_high */
	pte_off_even += offsetof(pte_t, pte_high);
	pte_off_odd += offsetof(pte_t, pte_high);
#endif

	if (IS_ENABLED(CONFIG_XPA)) {
		uasm_i_lw(p, tmp, pte_off_even, ptep); /* even pte */
		UASM_i_ROTR(p, tmp, tmp, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, tmp, C0_ENTRYLO0);

		if (cpu_has_xpa && !mips_xpa_disabled) {
			uasm_i_lw(p, tmp, 0, ptep);
			uasm_i_ext(p, tmp, tmp, 0, 24);
			uasm_i_mthc0(p, tmp, C0_ENTRYLO0);
		}

		uasm_i_lw(p, tmp, pte_off_odd, ptep); /* odd pte */
		UASM_i_ROTR(p, tmp, tmp, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, tmp, C0_ENTRYLO1);

		if (cpu_has_xpa && !mips_xpa_disabled) {
			uasm_i_lw(p, tmp, sizeof(pte_t), ptep);
			uasm_i_ext(p, tmp, tmp, 0, 24);
			uasm_i_mthc0(p, tmp, C0_ENTRYLO1);
		}
		return;
	}

	UASM_i_LW(p, tmp, pte_off_even, ptep); /* get even pte */
	UASM_i_LW(p, ptep, pte_off_odd, ptep); /* get odd pte */
	if (r45k_bvahwbug())
		build_tlb_probe_entry(p);
	build_convert_pte_to_entrylo(p, tmp);
	if (r4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTRYLO0);
	UASM_i_MTC0(p, tmp, C0_ENTRYLO0); /* load it */
	build_convert_pte_to_entrylo(p, ptep);
	if (r45k_bvahwbug())
		uasm_i_mfc0(p, tmp, C0_INDEX);
	if (r4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTRYLO1);
	UASM_i_MTC0(p, ptep, C0_ENTRYLO1); /* load it */
}