#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {unsigned long saved_tnpc; } ;
struct uprobe_task {unsigned long xol_vaddr; scalar_t__ vaddr; TYPE_1__ autask; } ;
struct pt_regs {scalar_t__ tnpc; scalar_t__ tpc; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long relbranch_fixup(u32 insn, struct uprobe_task *utask,
				     struct pt_regs *regs)
{
	/* Branch not taken, no mods necessary.  */
	if (regs->tnpc == regs->tpc + 0x4UL)
		return utask->autask.saved_tnpc + 0x4UL;

	/* The three cases are call, branch w/prediction,
	 * and traditional branch.
	 */
	if ((insn & 0xc0000000) == 0x40000000 ||
	    (insn & 0xc1c00000) == 0x00400000 ||
	    (insn & 0xc1c00000) == 0x00800000) {
		unsigned long real_pc = (unsigned long) utask->vaddr;
		unsigned long ixol_addr = utask->xol_vaddr;

		/* The instruction did all the work for us
		 * already, just apply the offset to the correct
		 * instruction location.
		 */
		return (real_pc + (regs->tnpc - ixol_addr));
	}

	/* It is jmpl or some other absolute PC modification instruction,
	 * leave NPC as-is.
	 */
	return regs->tnpc;
}