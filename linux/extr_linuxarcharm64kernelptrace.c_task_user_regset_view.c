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
struct user_regset_view {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct user_regset_view const user_aarch64_view ; 

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
#ifdef CONFIG_COMPAT
	/*
	 * Core dumping of 32-bit tasks or compat ptrace requests must use the
	 * user_aarch32_view compatible with arm32. Native ptrace requests on
	 * 32-bit children use an extended user_aarch32_ptrace_view to allow
	 * access to the TLS register.
	 */
	if (is_compat_task())
		return &user_aarch32_view;
	else if (is_compat_thread(task_thread_info(task)))
		return &user_aarch32_ptrace_view;
#endif
	return &user_aarch64_view;
}