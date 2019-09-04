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
struct pt_regs {int /*<<< orphan*/ * uregs; } ;
struct arch_uprobe_task {int /*<<< orphan*/  backup; } ;
struct arch_uprobe {size_t pcreg; } ;

/* Variables and functions */

__attribute__((used)) static void uprobe_unset_pc(struct arch_uprobe *auprobe,
			    struct arch_uprobe_task *autask,
			    struct pt_regs *regs)
{
	/* PC will be taken care of by common code */
	regs->uregs[auprobe->pcreg] = autask->backup;
}