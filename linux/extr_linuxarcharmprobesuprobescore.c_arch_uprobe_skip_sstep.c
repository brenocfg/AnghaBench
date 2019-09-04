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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* insn_singlestep ) (int /*<<< orphan*/ ,TYPE_1__*,struct pt_regs*) ;} ;
struct arch_uprobe {TYPE_1__ asi; scalar_t__ insn; int /*<<< orphan*/  simulate; } ;
typedef  int /*<<< orphan*/  probes_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_to_opcode_arm (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,struct pt_regs*) ; 

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	probes_opcode_t opcode;

	if (!auprobe->simulate)
		return false;

	opcode = __mem_to_opcode_arm(*(unsigned int *) auprobe->insn);

	auprobe->asi.insn_singlestep(opcode, &auprobe->asi, regs);

	return true;
}