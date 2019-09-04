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
struct pt_regs {int ARM_pc; int /*<<< orphan*/  ARM_cpsr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* insn_check_cc ) (int /*<<< orphan*/ ) ;} ;
struct arch_uprobe {TYPE_1__ asi; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bool arch_uprobe_ignore(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	if (!auprobe->asi.insn_check_cc(regs->ARM_cpsr)) {
		regs->ARM_pc += 4;
		return true;
	}

	return false;
}