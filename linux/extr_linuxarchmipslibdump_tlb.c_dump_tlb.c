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

/* Variables and functions */
 unsigned long CKSEG0 ; 
 int DIV_ROUND_UP (scalar_t__,int) ; 
 unsigned long long ENTRYLO_C ; 
 unsigned long long ENTRYLO_C_SHIFT ; 
 unsigned long long ENTRYLO_D ; 
 unsigned long long ENTRYLO_G ; 
 unsigned long long ENTRYLO_V ; 
 unsigned long MIPS_ENTRYHI_EHINV ; 
 unsigned long long MIPS_ENTRYLO_RI ; 
 unsigned long long MIPS_ENTRYLO_XI ; 
 unsigned int MIPS_GCTL1_RID ; 
 unsigned int MIPS_GCTL1_RID_SHIFT ; 
 unsigned long long PAGE_MASK ; 
 unsigned long cpu_asid_mask (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_has_guestid ; 
 scalar_t__ cpu_has_rixi ; 
 scalar_t__ cpu_has_tlbinv ; 
 int /*<<< orphan*/  current_cpu_data ; 
 scalar_t__ ilog2 (unsigned long) ; 
 int /*<<< orphan*/  msk2str (unsigned int) ; 
 int /*<<< orphan*/  mtc0_tlbr_hazard () ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long read_c0_entryhi () ; 
 unsigned long long read_c0_entrylo0 () ; 
 unsigned long long read_c0_entrylo1 () ; 
 unsigned int read_c0_guestctl1 () ; 
 unsigned int read_c0_index () ; 
 unsigned int read_c0_pagemask () ; 
 scalar_t__ readx_c0_entrylo0 () ; 
 scalar_t__ readx_c0_entrylo1 () ; 
 int /*<<< orphan*/  tlb_read () ; 
 int /*<<< orphan*/  tlb_read_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_guestctl1 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_index (unsigned int) ; 
 int /*<<< orphan*/  write_c0_pagemask (unsigned int) ; 

__attribute__((used)) static void dump_tlb(int first, int last)
{
	unsigned long s_entryhi, entryhi, asid;
	unsigned long long entrylo0, entrylo1, pa;
	unsigned int s_index, s_pagemask, s_guestctl1 = 0;
	unsigned int pagemask, guestctl1 = 0, c0, c1, i;
	unsigned long asidmask = cpu_asid_mask(&current_cpu_data);
	int asidwidth = DIV_ROUND_UP(ilog2(asidmask) + 1, 4);
#ifdef CONFIG_32BIT
	bool xpa = cpu_has_xpa && (read_c0_pagegrain() & PG_ELPA);
	int pwidth = xpa ? 11 : 8;
	int vwidth = 8;
#else
	bool xpa = false;
	int pwidth = 11;
	int vwidth = 11;
#endif

	s_pagemask = read_c0_pagemask();
	s_entryhi = read_c0_entryhi();
	s_index = read_c0_index();
	asid = s_entryhi & asidmask;
	if (cpu_has_guestid)
		s_guestctl1 = read_c0_guestctl1();

	for (i = first; i <= last; i++) {
		write_c0_index(i);
		mtc0_tlbr_hazard();
		tlb_read();
		tlb_read_hazard();
		pagemask = read_c0_pagemask();
		entryhi	 = read_c0_entryhi();
		entrylo0 = read_c0_entrylo0();
		entrylo1 = read_c0_entrylo1();
		if (cpu_has_guestid)
			guestctl1 = read_c0_guestctl1();

		/* EHINV bit marks entire entry as invalid */
		if (cpu_has_tlbinv && entryhi & MIPS_ENTRYHI_EHINV)
			continue;
		/*
		 * Prior to tlbinv, unused entries have a virtual address of
		 * CKSEG0.
		 */
		if ((entryhi & ~0x1ffffUL) == CKSEG0)
			continue;
		/*
		 * ASID takes effect in absence of G (global) bit.
		 * We check both G bits, even though architecturally they should
		 * match one another, because some revisions of the SB1 core may
		 * leave only a single G bit set after a machine check exception
		 * due to duplicate TLB entry.
		 */
		if (!((entrylo0 | entrylo1) & ENTRYLO_G) &&
		    (entryhi & asidmask) != asid)
			continue;

		/*
		 * Only print entries in use
		 */
		printk("Index: %2d pgmask=%s ", i, msk2str(pagemask));

		c0 = (entrylo0 & ENTRYLO_C) >> ENTRYLO_C_SHIFT;
		c1 = (entrylo1 & ENTRYLO_C) >> ENTRYLO_C_SHIFT;

		pr_cont("va=%0*lx asid=%0*lx",
			vwidth, (entryhi & ~0x1fffUL),
			asidwidth, entryhi & asidmask);
		if (cpu_has_guestid)
			pr_cont(" gid=%02lx",
				(guestctl1 & MIPS_GCTL1_RID)
					>> MIPS_GCTL1_RID_SHIFT);
		/* RI/XI are in awkward places, so mask them off separately */
		pa = entrylo0 & ~(MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI);
		if (xpa)
			pa |= (unsigned long long)readx_c0_entrylo0() << 30;
		pa = (pa << 6) & PAGE_MASK;
		pr_cont("\n\t[");
		if (cpu_has_rixi)
			pr_cont("ri=%d xi=%d ",
				(entrylo0 & MIPS_ENTRYLO_RI) ? 1 : 0,
				(entrylo0 & MIPS_ENTRYLO_XI) ? 1 : 0);
		pr_cont("pa=%0*llx c=%d d=%d v=%d g=%d] [",
			pwidth, pa, c0,
			(entrylo0 & ENTRYLO_D) ? 1 : 0,
			(entrylo0 & ENTRYLO_V) ? 1 : 0,
			(entrylo0 & ENTRYLO_G) ? 1 : 0);
		/* RI/XI are in awkward places, so mask them off separately */
		pa = entrylo1 & ~(MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI);
		if (xpa)
			pa |= (unsigned long long)readx_c0_entrylo1() << 30;
		pa = (pa << 6) & PAGE_MASK;
		if (cpu_has_rixi)
			pr_cont("ri=%d xi=%d ",
				(entrylo1 & MIPS_ENTRYLO_RI) ? 1 : 0,
				(entrylo1 & MIPS_ENTRYLO_XI) ? 1 : 0);
		pr_cont("pa=%0*llx c=%d d=%d v=%d g=%d]\n",
			pwidth, pa, c1,
			(entrylo1 & ENTRYLO_D) ? 1 : 0,
			(entrylo1 & ENTRYLO_V) ? 1 : 0,
			(entrylo1 & ENTRYLO_G) ? 1 : 0);
	}
	printk("\n");

	write_c0_entryhi(s_entryhi);
	write_c0_index(s_index);
	write_c0_pagemask(s_pagemask);
	if (cpu_has_guestid)
		write_c0_guestctl1(s_guestctl1);
}