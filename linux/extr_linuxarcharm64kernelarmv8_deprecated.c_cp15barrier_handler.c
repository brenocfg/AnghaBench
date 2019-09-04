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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int /*<<< orphan*/  pc; int /*<<< orphan*/  pstate; } ;
struct TYPE_2__ {scalar_t__ pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
#define  ARM_OPCODE_CONDTEST_FAIL 130 
#define  ARM_OPCODE_CONDTEST_PASS 129 
#define  ARM_OPCODE_CONDTEST_UNCOND 128 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 int aarch32_check_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aarch32_insn_mcr_extract_crm (int /*<<< orphan*/ ) ; 
 int aarch32_insn_mcr_extract_opc2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm64_skip_faulting_instruction (struct pt_regs*,int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  trace_instruction_emulation (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp15barrier_handler(struct pt_regs *regs, u32 instr)
{
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->pc);

	switch (aarch32_check_condition(instr, regs->pstate)) {
	case ARM_OPCODE_CONDTEST_PASS:
		break;
	case ARM_OPCODE_CONDTEST_FAIL:
		/* Condition failed - return to next instruction */
		goto ret;
	case ARM_OPCODE_CONDTEST_UNCOND:
		/* If unconditional encoding - not a barrier instruction */
		return -EFAULT;
	default:
		return -EINVAL;
	}

	switch (aarch32_insn_mcr_extract_crm(instr)) {
	case 10:
		/*
		 * dmb - mcr p15, 0, Rt, c7, c10, 5
		 * dsb - mcr p15, 0, Rt, c7, c10, 4
		 */
		if (aarch32_insn_mcr_extract_opc2(instr) == 5) {
			dmb(sy);
			trace_instruction_emulation(
				"mcr p15, 0, Rt, c7, c10, 5 ; dmb", regs->pc);
		} else {
			dsb(sy);
			trace_instruction_emulation(
				"mcr p15, 0, Rt, c7, c10, 4 ; dsb", regs->pc);
		}
		break;
	case 5:
		/*
		 * isb - mcr p15, 0, Rt, c7, c5, 4
		 *
		 * Taking an exception or returning from one acts as an
		 * instruction barrier. So no explicit barrier needed here.
		 */
		trace_instruction_emulation(
			"mcr p15, 0, Rt, c7, c5, 4 ; isb", regs->pc);
		break;
	}

ret:
	pr_warn_ratelimited("\"%s\" (%ld) uses deprecated CP15 Barrier instruction at 0x%llx\n",
			current->comm, (unsigned long)current->pid, regs->pc);

	arm64_skip_faulting_instruction(regs, 4);
	return 0;
}