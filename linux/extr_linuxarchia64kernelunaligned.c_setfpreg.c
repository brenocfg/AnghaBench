#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct switch_stack {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  cr_ipsr; } ;
struct ia64_fpreg {int dummy; } ;
struct TYPE_4__ {struct ia64_fpreg* fph; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,unsigned long,scalar_t__) ; 
 scalar_t__ FR_IN_SW (unsigned long) ; 
 scalar_t__ FR_OFFS (unsigned long) ; 
 unsigned long IA64_FIRST_ROTATING_FR ; 
 int /*<<< orphan*/  IA64_PSR_MFL ; 
 TYPE_2__* current ; 
 size_t fph_index (struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  ia64_sync_fph (TYPE_2__*) ; 

__attribute__((used)) static void
setfpreg (unsigned long regnum, struct ia64_fpreg *fpval, struct pt_regs *regs)
{
	struct switch_stack *sw = (struct switch_stack *)regs - 1;
	unsigned long addr;

	/*
	 * From EAS-2.5: FPDisableFault has higher priority than Unaligned
	 * Fault. Thus, when we get here, we know the partition is enabled.
	 * To update f32-f127, there are three choices:
	 *
	 *	(1) save f32-f127 to thread.fph and update the values there
	 *	(2) use a gigantic switch statement to directly access the registers
	 *	(3) generate code on the fly to update the desired register
	 *
	 * For now, we are using approach (1).
	 */
	if (regnum >= IA64_FIRST_ROTATING_FR) {
		ia64_sync_fph(current);
		current->thread.fph[fph_index(regs, regnum)] = *fpval;
	} else {
		/*
		 * pt_regs or switch_stack ?
		 */
		if (FR_IN_SW(regnum)) {
			addr = (unsigned long)sw;
		} else {
			addr = (unsigned long)regs;
		}

		DPRINT("tmp_base=%lx offset=%d\n", addr, FR_OFFS(regnum));

		addr += FR_OFFS(regnum);
		*(struct ia64_fpreg *)addr = *fpval;

		/*
		 * mark the low partition as being used now
		 *
		 * It is highly unlikely that this bit is not already set, but
		 * let's do it for safety.
		 */
		regs->cr_ipsr |= IA64_PSR_MFL;
	}
}