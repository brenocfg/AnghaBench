#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sa_flags; } ;
struct k_sigaction {TYPE_1__ sa; } ;

/* Variables and functions */
 int SA_IA32_ABI ; 
 int SA_X32_ABI ; 
 scalar_t__ in_ia32_syscall () ; 
 scalar_t__ in_x32_syscall () ; 
 int /*<<< orphan*/  signal_compat_build_tests () ; 

void sigaction_compat_abi(struct k_sigaction *act, struct k_sigaction *oact)
{
	signal_compat_build_tests();

	/* Don't leak in-kernel non-uapi flags to user-space */
	if (oact)
		oact->sa.sa_flags &= ~(SA_IA32_ABI | SA_X32_ABI);

	if (!act)
		return;

	/* Don't let flags to be set from userspace */
	act->sa.sa_flags &= ~(SA_IA32_ABI | SA_X32_ABI);

	if (in_ia32_syscall())
		act->sa.sa_flags |= SA_IA32_ABI;
	if (in_x32_syscall())
		act->sa.sa_flags |= SA_X32_ABI;
}