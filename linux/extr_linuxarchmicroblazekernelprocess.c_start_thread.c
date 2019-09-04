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
struct pt_regs {unsigned long pc; unsigned long r1; scalar_t__ pt_mode; } ;

/* Variables and functions */

void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long usp)
{
	regs->pc = pc;
	regs->r1 = usp;
	regs->pt_mode = 0;
#ifdef CONFIG_MMU
	regs->msr |= MSR_UMS;
	regs->msr &= ~MSR_VM;
#endif
}