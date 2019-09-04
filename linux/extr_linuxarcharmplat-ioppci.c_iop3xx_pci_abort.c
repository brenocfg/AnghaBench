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
struct pt_regs {int ARM_pc; int /*<<< orphan*/  ARM_lr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop3xx_pci_abort(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{
	DBG("PCI abort: address = 0x%08lx fsr = 0x%03x PC = 0x%08lx LR = 0x%08lx\n",
		addr, fsr, regs->ARM_pc, regs->ARM_lr);

	/*
	 * If it was an imprecise abort, then we need to correct the
	 * return address to be _after_ the instruction.
	 */
	if (fsr & (1 << 10))
		regs->ARM_pc += 4;

	return 0;
}