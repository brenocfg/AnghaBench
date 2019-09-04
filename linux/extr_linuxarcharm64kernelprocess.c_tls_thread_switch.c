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
struct TYPE_3__ {int /*<<< orphan*/  tp_value; } ;
struct TYPE_4__ {TYPE_1__ uw; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm64_kernel_unmapped_at_el0 () ; 
 scalar_t__ is_compat_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/ * task_user_tls (struct task_struct*) ; 
 int /*<<< orphan*/  tls_preserve_current_state () ; 
 int /*<<< orphan*/  tpidr_el0 ; 
 int /*<<< orphan*/  tpidrro_el0 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tls_thread_switch(struct task_struct *next)
{
	tls_preserve_current_state();

	if (is_compat_thread(task_thread_info(next)))
		write_sysreg(next->thread.uw.tp_value, tpidrro_el0);
	else if (!arm64_kernel_unmapped_at_el0())
		write_sysreg(0, tpidrro_el0);

	write_sysreg(*task_user_tls(next), tpidr_el0);
}