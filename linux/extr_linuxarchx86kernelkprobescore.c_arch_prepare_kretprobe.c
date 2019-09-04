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
struct kretprobe_instance {unsigned long* fp; int /*<<< orphan*/ * ret_addr; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  kretprobe_trampoline ; 
 unsigned long* stack_addr (struct pt_regs*) ; 

void arch_prepare_kretprobe(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	unsigned long *sara = stack_addr(regs);

	ri->ret_addr = (kprobe_opcode_t *) *sara;
	ri->fp = sara;

	/* Replace the return addr with trampoline addr */
	*sara = (unsigned long) &kretprobe_trampoline;
}