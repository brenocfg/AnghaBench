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
typedef  int u32 ;
struct idle_statedata {scalar_t__ mpu_state; scalar_t__ mpu_logic_state; int /*<<< orphan*/  cpu_state; } ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {size_t cpu; } ;

/* Variables and functions */
 scalar_t__ IS_PM44XX_ERRATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD ; 
 scalar_t__ PWRDM_POWER_OFF ; 
 scalar_t__ PWRDM_POWER_ON ; 
 scalar_t__ PWRDM_POWER_RET ; 
 int /*<<< orphan*/  abort_barrier ; 
 int /*<<< orphan*/  clkdm_allow_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdm_deny_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_clkdm ; 
 int /*<<< orphan*/  cpu_cluster_pm_enter () ; 
 int /*<<< orphan*/  cpu_cluster_pm_exit () ; 
 int* cpu_done ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/ * cpu_pd ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpuidle_coupled_parallel_barrier (struct cpuidle_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_dist_disable () ; 
 scalar_t__ gic_dist_disabled () ; 
 int /*<<< orphan*/  gic_timer_retrigger () ; 
 int /*<<< orphan*/  mpu_pd ; 
 int /*<<< orphan*/  omap4_enter_lowpower (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_pwrdm_state (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pwrdm_read_pwrst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_logic_retst (int /*<<< orphan*/ ,scalar_t__) ; 
 struct idle_statedata* state_ptr ; 
 int /*<<< orphan*/  tick_broadcast_enable () ; 
 int /*<<< orphan*/  tick_broadcast_enter () ; 
 int /*<<< orphan*/  tick_broadcast_exit () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int omap_enter_idle_coupled(struct cpuidle_device *dev,
			struct cpuidle_driver *drv,
			int index)
{
	struct idle_statedata *cx = state_ptr + index;
	u32 mpuss_can_lose_context = 0;

	/*
	 * CPU0 has to wait and stay ON until CPU1 is OFF state.
	 * This is necessary to honour hardware recommondation
	 * of triggeing all the possible low power modes once CPU1 is
	 * out of coherency and in OFF mode.
	 */
	if (dev->cpu == 0 && cpumask_test_cpu(1, cpu_online_mask)) {
		while (pwrdm_read_pwrst(cpu_pd[1]) != PWRDM_POWER_OFF) {
			cpu_relax();

			/*
			 * CPU1 could have already entered & exited idle
			 * without hitting off because of a wakeup
			 * or a failed attempt to hit off mode.  Check for
			 * that here, otherwise we could spin forever
			 * waiting for CPU1 off.
			 */
			if (cpu_done[1])
			    goto fail;

		}
	}

	mpuss_can_lose_context = (cx->mpu_state == PWRDM_POWER_RET) &&
				 (cx->mpu_logic_state == PWRDM_POWER_OFF);

	/* Enter broadcast mode for periodic timers */
	tick_broadcast_enable();

	/* Enter broadcast mode for one-shot timers */
	tick_broadcast_enter();

	/*
	 * Call idle CPU PM enter notifier chain so that
	 * VFP and per CPU interrupt context is saved.
	 */
	cpu_pm_enter();

	if (dev->cpu == 0) {
		pwrdm_set_logic_retst(mpu_pd, cx->mpu_logic_state);
		omap_set_pwrdm_state(mpu_pd, cx->mpu_state);

		/*
		 * Call idle CPU cluster PM enter notifier chain
		 * to save GIC and wakeupgen context.
		 */
		if (mpuss_can_lose_context)
			cpu_cluster_pm_enter();
	}

	omap4_enter_lowpower(dev->cpu, cx->cpu_state);
	cpu_done[dev->cpu] = true;

	/* Wakeup CPU1 only if it is not offlined */
	if (dev->cpu == 0 && cpumask_test_cpu(1, cpu_online_mask)) {

		if (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD) &&
		    mpuss_can_lose_context)
			gic_dist_disable();

		clkdm_deny_idle(cpu_clkdm[1]);
		omap_set_pwrdm_state(cpu_pd[1], PWRDM_POWER_ON);
		clkdm_allow_idle(cpu_clkdm[1]);

		if (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD) &&
		    mpuss_can_lose_context) {
			while (gic_dist_disabled()) {
				udelay(1);
				cpu_relax();
			}
			gic_timer_retrigger();
		}
	}

	/*
	 * Call idle CPU PM exit notifier chain to restore
	 * VFP and per CPU IRQ context.
	 */
	cpu_pm_exit();

	/*
	 * Call idle CPU cluster PM exit notifier chain
	 * to restore GIC and wakeupgen context.
	 */
	if (dev->cpu == 0 && mpuss_can_lose_context)
		cpu_cluster_pm_exit();

	tick_broadcast_exit();

fail:
	cpuidle_coupled_parallel_barrier(dev, &abort_barrier);
	cpu_done[dev->cpu] = false;

	return index;
}