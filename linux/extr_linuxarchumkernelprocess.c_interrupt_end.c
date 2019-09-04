#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_3__ {struct pt_regs regs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  do_signal (struct pt_regs*) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ test_and_clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_notify_resume (struct pt_regs*) ; 

void interrupt_end(void)
{
	struct pt_regs *regs = &current->thread.regs;

	if (need_resched())
		schedule();
	if (test_thread_flag(TIF_SIGPENDING))
		do_signal(regs);
	if (test_and_clear_thread_flag(TIF_NOTIFY_RESUME))
		tracehook_notify_resume(regs);
}