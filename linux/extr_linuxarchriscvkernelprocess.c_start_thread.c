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
struct pt_regs {int sstatus; unsigned long sepc; unsigned long sp; } ;

/* Variables and functions */
 int SR_FS_INITIAL ; 
 int SR_SPIE ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

void start_thread(struct pt_regs *regs, unsigned long pc,
	unsigned long sp)
{
	regs->sstatus = SR_SPIE /* User mode, irqs on */ | SR_FS_INITIAL;
	regs->sepc = pc;
	regs->sp = sp;
	set_fs(USER_DS);
}