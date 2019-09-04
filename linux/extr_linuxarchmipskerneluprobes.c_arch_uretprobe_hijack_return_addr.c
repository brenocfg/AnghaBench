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
struct pt_regs {unsigned long* regs; } ;

/* Variables and functions */

unsigned long arch_uretprobe_hijack_return_addr(
	unsigned long trampoline_vaddr, struct pt_regs *regs)
{
	unsigned long ra;

	ra = regs->regs[31];

	/* Replace the return address with the trampoline address */
	regs->regs[31] = trampoline_vaddr;

	return ra;
}