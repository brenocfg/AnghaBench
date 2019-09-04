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
struct pt_regs {int /*<<< orphan*/  ARM_cpsr; int /*<<< orphan*/  ARM_pc; int /*<<< orphan*/  ARM_lr; int /*<<< orphan*/  ARM_sp; int /*<<< orphan*/  ARM_ip; int /*<<< orphan*/  ARM_fp; int /*<<< orphan*/  ARM_r10; int /*<<< orphan*/  ARM_r9; int /*<<< orphan*/  ARM_r8; int /*<<< orphan*/  ARM_r7; int /*<<< orphan*/  ARM_r6; int /*<<< orphan*/  ARM_r5; int /*<<< orphan*/  ARM_r4; int /*<<< orphan*/  ARM_r3; int /*<<< orphan*/  ARM_r2; int /*<<< orphan*/  ARM_r1; int /*<<< orphan*/  ARM_r0; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void print_registers(struct pt_regs *regs)
{
	pr_err("r0  %08lx | r1  %08lx | r2  %08lx | r3  %08lx\n",
		regs->ARM_r0, regs->ARM_r1, regs->ARM_r2, regs->ARM_r3);
	pr_err("r4  %08lx | r5  %08lx | r6  %08lx | r7  %08lx\n",
		regs->ARM_r4, regs->ARM_r5, regs->ARM_r6, regs->ARM_r7);
	pr_err("r8  %08lx | r9  %08lx | r10 %08lx | r11 %08lx\n",
		regs->ARM_r8, regs->ARM_r9, regs->ARM_r10, regs->ARM_fp);
	pr_err("r12 %08lx | sp  %08lx | lr  %08lx | pc  %08lx\n",
		regs->ARM_ip, regs->ARM_sp, regs->ARM_lr, regs->ARM_pc);
	pr_err("cpsr %08lx\n", regs->ARM_cpsr);
}