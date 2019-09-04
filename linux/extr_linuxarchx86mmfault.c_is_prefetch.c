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
 scalar_t__ TASK_SIZE_MAX ; 
 unsigned long X86_PF_INSTR ; 
 int /*<<< orphan*/  check_prefetch_opcode (struct pt_regs*,unsigned char*,unsigned char,int*) ; 
 scalar_t__ convert_ip_to_linear (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ probe_kernel_address (unsigned char*,unsigned char) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int
is_prefetch(struct pt_regs *regs, unsigned long error_code, unsigned long addr)
{
	unsigned char *max_instr;
	unsigned char *instr;
	int prefetch = 0;

	/*
	 * If it was a exec (instruction fetch) fault on NX page, then
	 * do not ignore the fault:
	 */
	if (error_code & X86_PF_INSTR)
		return 0;

	instr = (void *)convert_ip_to_linear(current, regs);
	max_instr = instr + 15;

	if (user_mode(regs) && instr >= (unsigned char *)TASK_SIZE_MAX)
		return 0;

	while (instr < max_instr) {
		unsigned char opcode;

		if (probe_kernel_address(instr, opcode))
			break;

		instr++;

		if (!check_prefetch_opcode(regs, instr, opcode, &prefetch))
			break;
	}
	return prefetch;
}