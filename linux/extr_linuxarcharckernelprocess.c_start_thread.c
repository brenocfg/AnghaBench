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
struct pt_regs {unsigned long sp; unsigned long ret; int status32; int lp_start; int lp_end; } ;

/* Variables and functions */
 int ISA_INIT_STATUS_BITS ; 
 int STATUS_L_MASK ; 
 int STATUS_U_MASK ; 

void start_thread(struct pt_regs * regs, unsigned long pc, unsigned long usp)
{
	regs->sp = usp;
	regs->ret = pc;

	/*
	 * [U]ser Mode bit set
	 * [L] ZOL loop inhibited to begin with - cleared by a LP insn
	 * Interrupts enabled
	 */
	regs->status32 = STATUS_U_MASK | STATUS_L_MASK | ISA_INIT_STATUS_BITS;

#ifdef CONFIG_EZNPS_MTM_EXT
	regs->eflags = 0;
#endif

	/* bogus seed values for debugging */
	regs->lp_start = 0x10;
	regs->lp_end = 0x80;
}