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

/* Variables and functions */
 int CPU_PM_CPU_IDLE_ENTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arch_cpu_idle_enter () ; 
 int /*<<< orphan*/  arch_cpu_idle_exit () ; 
 int /*<<< orphan*/  arm_cpuidle_suspend ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int tick_broadcast_enter () ; 
 int /*<<< orphan*/  tick_broadcast_exit () ; 

__attribute__((used)) static int suspend_cpu(int index, bool broadcast)
{
	int ret;

	arch_cpu_idle_enter();

	if (broadcast) {
		/*
		 * The local timer will be shut down, we need to enter tick
		 * broadcast.
		 */
		ret = tick_broadcast_enter();
		if (ret) {
			/*
			 * In the absence of hardware broadcast mechanism,
			 * this CPU might be used to broadcast wakeups, which
			 * may be why entering tick broadcast has failed.
			 * There is little the kernel can do to work around
			 * that, so enter WFI instead (idle state 0).
			 */
			cpu_do_idle();
			ret = 0;
			goto out_arch_exit;
		}
	}

	/*
	 * Replicate the common ARM cpuidle enter function
	 * (arm_enter_idle_state).
	 */
	ret = CPU_PM_CPU_IDLE_ENTER(arm_cpuidle_suspend, index);

	if (broadcast)
		tick_broadcast_exit();

out_arch_exit:
	arch_cpu_idle_exit();

	return ret;
}