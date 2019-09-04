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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long procedure_link_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  procedure_link_pointer_set (struct pt_regs*,unsigned long) ; 

unsigned long
arch_uretprobe_hijack_return_addr(unsigned long trampoline_vaddr,
				  struct pt_regs *regs)
{
	unsigned long orig_ret_vaddr;

	orig_ret_vaddr = procedure_link_pointer(regs);
	/* Replace the return addr with trampoline addr */
	procedure_link_pointer_set(regs, trampoline_vaddr);

	return orig_ret_vaddr;
}