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
struct pt_regs {unsigned long link; } ;
struct kretprobe_instance {int /*<<< orphan*/ * ret_addr; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 scalar_t__ kretprobe_trampoline ; 

void arch_prepare_kretprobe(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	ri->ret_addr = (kprobe_opcode_t *)regs->link;

	/* Replace the return addr with trampoline addr */
	regs->link = (unsigned long)kretprobe_trampoline;
}