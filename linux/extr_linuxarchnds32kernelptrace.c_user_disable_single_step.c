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
struct task_struct {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  ipsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSW_mskHSS ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void user_disable_single_step(struct task_struct *child)
{
	struct pt_regs *regs;
	regs = task_pt_regs(child);
	regs->ipsw &= ~PSW_mskHSS;
	clear_tsk_thread_flag(child, TIF_SINGLESTEP);
}