#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  saved_trap_nr; } ;
struct uprobe_task {int /*<<< orphan*/  vaddr; TYPE_2__ autask; } ;
struct pt_regs {int dummy; } ;
struct arch_uprobe {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  trap_nr; } ;
struct TYPE_7__ {TYPE_1__ thread; struct uprobe_task* utask; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  instruction_pointer_set (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_disable_single_step (TYPE_3__*) ; 

void arch_uprobe_abort_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;

	current->thread.trap_nr = utask->autask.saved_trap_nr;
	instruction_pointer_set(regs, utask->vaddr);

	user_disable_single_step(current);
}