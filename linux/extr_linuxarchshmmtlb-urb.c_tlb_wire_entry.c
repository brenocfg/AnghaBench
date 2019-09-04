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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MMUCR ; 
 unsigned long MMUCR_URB ; 
 int MMUCR_URB_NENTRIES ; 
 unsigned long MMUCR_URB_SHIFT ; 
 unsigned long MMUCR_URC ; 
 int MMUCR_URC_SHIFT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __update_tlb (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void tlb_wire_entry(struct vm_area_struct *vma, unsigned long addr, pte_t pte)
{
	unsigned long status, flags;
	int urb;

	local_irq_save(flags);

	status = __raw_readl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URC;

	/*
	 * Make sure we're not trying to wire the last TLB entry slot.
	 */
	BUG_ON(!--urb);

	urb = urb % MMUCR_URB_NENTRIES;

	/*
	 * Insert this entry into the highest non-wired TLB slot (via
	 * the URC field).
	 */
	status |= (urb << MMUCR_URC_SHIFT);
	__raw_writel(status, MMUCR);
	ctrl_barrier();

	/* Load the entry into the TLB */
	__update_tlb(vma, addr, pte);

	/* ... and wire it up. */
	status = __raw_readl(MMUCR);

	status &= ~MMUCR_URB;
	status |= (urb << MMUCR_URB_SHIFT);

	__raw_writel(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
}