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
typedef  scalar_t__ u32 ;
struct pt_regs {int /*<<< orphan*/  pc; int /*<<< orphan*/  pstate; } ;
struct TYPE_2__ {scalar_t__ pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 int /*<<< orphan*/  PSR_AA32_E_BIT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_instruction_emulation (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compat_setend_handler(struct pt_regs *regs, u32 big_endian)
{
	char *insn;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->pc);

	if (big_endian) {
		insn = "setend be";
		regs->pstate |= PSR_AA32_E_BIT;
	} else {
		insn = "setend le";
		regs->pstate &= ~PSR_AA32_E_BIT;
	}

	trace_instruction_emulation(insn, regs->pc);
	pr_warn_ratelimited("\"%s\" (%ld) uses deprecated setend instruction at 0x%llx\n",
			current->comm, (unsigned long)current->pid, regs->pc);

	return 0;
}