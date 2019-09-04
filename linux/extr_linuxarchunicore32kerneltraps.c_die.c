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
struct thread_info {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int __die (char const*,int,struct thread_info*,struct pt_regs*) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  oops_enter () ; 
 int /*<<< orphan*/  oops_exit () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void die(const char *str, struct pt_regs *regs, int err)
{
	struct thread_info *thread = current_thread_info();
	int ret;

	oops_enter();

	spin_lock_irq(&die_lock);
	console_verbose();
	bust_spinlocks(1);
	ret = __die(str, err, thread, regs);

	bust_spinlocks(0);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);
	oops_exit();

	if (in_interrupt())
		panic("Fatal exception in interrupt");
	if (panic_on_oops)
		panic("Fatal exception");
	if (ret != NOTIFY_STOP)
		do_exit(SIGSEGV);
}