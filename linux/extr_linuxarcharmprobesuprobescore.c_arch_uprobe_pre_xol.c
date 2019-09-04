#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  saved_trap_no; } ;
struct uprobe_task {int /*<<< orphan*/  xol_vaddr; TYPE_2__ autask; } ;
struct pt_regs {int /*<<< orphan*/  ARM_pc; } ;
struct arch_uprobe {int /*<<< orphan*/  (* prehandler ) (struct arch_uprobe*,TYPE_2__*,struct pt_regs*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  trap_no; } ;
struct TYPE_6__ {TYPE_1__ thread; struct uprobe_task* utask; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPROBE_TRAP_NR ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  stub1 (struct arch_uprobe*,TYPE_2__*,struct pt_regs*) ; 

int arch_uprobe_pre_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;

	if (auprobe->prehandler)
		auprobe->prehandler(auprobe, &utask->autask, regs);

	utask->autask.saved_trap_no = current->thread.trap_no;
	current->thread.trap_no = UPROBE_TRAP_NR;
	regs->ARM_pc = utask->xol_vaddr;

	return 0;
}