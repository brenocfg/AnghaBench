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
struct user_fpsimd_state {int /*<<< orphan*/  fpsr; } ;
struct TYPE_4__ {scalar_t__ sve_vl; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SI_KERNEL ; 
 int /*<<< orphan*/  TIF_FOREIGN_FPSTATE ; 
 int /*<<< orphan*/  TIF_SVE ; 
 scalar_t__ WARN_ON (int) ; 
 struct user_fpsimd_state* __this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  force_signal_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fpsimd_last_state ; 
 int /*<<< orphan*/  fpsimd_save_state (struct user_fpsimd_state*) ; 
 int /*<<< orphan*/  in_softirq () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ sve_get_vl () ; 
 int /*<<< orphan*/  sve_pffr (TYPE_1__*) ; 
 int /*<<< orphan*/  sve_save_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ system_supports_sve () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void fpsimd_save(void)
{
	struct user_fpsimd_state *st = __this_cpu_read(fpsimd_last_state.st);
	/* set by fpsimd_bind_task_to_cpu() or fpsimd_bind_state_to_cpu() */

	WARN_ON(!in_softirq() && !irqs_disabled());

	if (!test_thread_flag(TIF_FOREIGN_FPSTATE)) {
		if (system_supports_sve() && test_thread_flag(TIF_SVE)) {
			if (WARN_ON(sve_get_vl() != current->thread.sve_vl)) {
				/*
				 * Can't save the user regs, so current would
				 * re-enter user with corrupt state.
				 * There's no way to recover, so kill it:
				 */
				force_signal_inject(SIGKILL, SI_KERNEL, 0);
				return;
			}

			sve_save_state(sve_pffr(&current->thread), &st->fpsr);
		} else
			fpsimd_save_state(st);
	}
}