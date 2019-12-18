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
struct gru_tlb_fault_handle {int dummy; } ;
struct gru_thread_state {int dummy; } ;
struct gru_state {int /*<<< orphan*/  gs_gid; } ;
struct gru_control_block_extended {scalar_t__ opccpy; unsigned long cbe_baddr0; unsigned long cbe_src_cl; unsigned long cbe_baddr1; int xtypecpy; int cbe_nelemcur; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAA_RAM ; 
 unsigned long GRU_CACHE_LINE_BYTES ; 
 int /*<<< orphan*/  GRU_PAGESIZE (int) ; 
 scalar_t__ OP_BCOPY ; 
 unsigned long PAGE_MASK ; 
 unsigned char PAGE_SIZE ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct gru_thread_state*,struct gru_tlb_fault_handle*,unsigned long,int,int,int,unsigned long) ; 
 int gru_vtop (struct gru_thread_state*,unsigned long,int,int,unsigned long*,int*) ; 
 int /*<<< orphan*/  grudev ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ tfh_write_only (struct gru_tlb_fault_handle*,unsigned long,int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_preload_page ; 

__attribute__((used)) static void gru_preload_tlb(struct gru_state *gru,
			struct gru_thread_state *gts, int atomic,
			unsigned long fault_vaddr, int asid, int write,
			unsigned char tlb_preload_count,
			struct gru_tlb_fault_handle *tfh,
			struct gru_control_block_extended *cbe)
{
	unsigned long vaddr = 0, gpa;
	int ret, pageshift;

	if (cbe->opccpy != OP_BCOPY)
		return;

	if (fault_vaddr == cbe->cbe_baddr0)
		vaddr = fault_vaddr + GRU_CACHE_LINE_BYTES * cbe->cbe_src_cl - 1;
	else if (fault_vaddr == cbe->cbe_baddr1)
		vaddr = fault_vaddr + (1 << cbe->xtypecpy) * cbe->cbe_nelemcur - 1;

	fault_vaddr &= PAGE_MASK;
	vaddr &= PAGE_MASK;
	vaddr = min(vaddr, fault_vaddr + tlb_preload_count * PAGE_SIZE);

	while (vaddr > fault_vaddr) {
		ret = gru_vtop(gts, vaddr, write, atomic, &gpa, &pageshift);
		if (ret || tfh_write_only(tfh, gpa, GAA_RAM, vaddr, asid, write,
					  GRU_PAGESIZE(pageshift)))
			return;
		gru_dbg(grudev,
			"%s: gid %d, gts 0x%p, tfh 0x%p, vaddr 0x%lx, asid 0x%x, rw %d, ps %d, gpa 0x%lx\n",
			atomic ? "atomic" : "non-atomic", gru->gs_gid, gts, tfh,
			vaddr, asid, write, pageshift, gpa);
		vaddr -= PAGE_SIZE;
		STAT(tlb_preload_page);
	}
}