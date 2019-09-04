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
 unsigned int ESR_ELx_WNR ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  die_kernel_fault (char const*,unsigned long,unsigned int,struct pt_regs*) ; 
 scalar_t__ fixup_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  is_el1_instruction_abort (unsigned int) ; 
 scalar_t__ is_el1_permission_fault (unsigned int,struct pt_regs*,unsigned long) ; 

__attribute__((used)) static void __do_kernel_fault(unsigned long addr, unsigned int esr,
			      struct pt_regs *regs)
{
	const char *msg;

	/*
	 * Are we prepared to handle this kernel fault?
	 * We are almost certainly not prepared to handle instruction faults.
	 */
	if (!is_el1_instruction_abort(esr) && fixup_exception(regs))
		return;

	if (is_el1_permission_fault(esr, regs, addr)) {
		if (esr & ESR_ELx_WNR)
			msg = "write to read-only memory";
		else
			msg = "read from unreadable memory";
	} else if (addr < PAGE_SIZE) {
		msg = "NULL pointer dereference";
	} else {
		msg = "paging request";
	}

	die_kernel_fault(msg, addr, esr, regs);
}