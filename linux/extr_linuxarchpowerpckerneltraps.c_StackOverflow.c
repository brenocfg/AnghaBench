#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/ * gpr; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  debugger (struct pt_regs*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

void StackOverflow(struct pt_regs *regs)
{
	pr_crit("Kernel stack overflow in process %s[%d], r1=%lx\n",
		current->comm, task_pid_nr(current), regs->gpr[1]);
	debugger(regs);
	show_regs(regs);
	panic("kernel stack overflow");
}