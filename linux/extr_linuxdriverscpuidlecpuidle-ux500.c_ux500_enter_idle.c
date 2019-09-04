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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_AP_IDLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  master ; 
 int /*<<< orphan*/  master_lock ; 
 scalar_t__ num_online_cpus () ; 
 scalar_t__ prcmu_copy_gic_settings () ; 
 scalar_t__ prcmu_gic_decouple () ; 
 scalar_t__ prcmu_gic_pending_irq () ; 
 int /*<<< orphan*/  prcmu_gic_recouple () ; 
 int /*<<< orphan*/  prcmu_is_cpu_in_wfi (int) ; 
 scalar_t__ prcmu_pending_irq () ; 
 scalar_t__ prcmu_set_power_state (int /*<<< orphan*/ ,int,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ux500_enter_idle(struct cpuidle_device *dev,
				   struct cpuidle_driver *drv, int index)
{
	int this_cpu = smp_processor_id();
	bool recouple = false;

	if (atomic_inc_return(&master) == num_online_cpus()) {

		/* With this lock, we prevent the other cpu to exit and enter
		 * this function again and become the master */
		if (!spin_trylock(&master_lock))
			goto wfi;

		/* decouple the gic from the A9 cores */
		if (prcmu_gic_decouple()) {
			spin_unlock(&master_lock);
			goto out;
		}

		/* If an error occur, we will have to recouple the gic
		 * manually */
		recouple = true;

		/* At this state, as the gic is decoupled, if the other
		 * cpu is in WFI, we have the guarantee it won't be wake
		 * up, so we can safely go to retention */
		if (!prcmu_is_cpu_in_wfi(this_cpu ? 0 : 1))
			goto out;

		/* The prcmu will be in charge of watching the interrupts
		 * and wake up the cpus */
		if (prcmu_copy_gic_settings())
			goto out;

		/* Check in the meantime an interrupt did
		 * not occur on the gic ... */
		if (prcmu_gic_pending_irq())
			goto out;

		/* ... and the prcmu */
		if (prcmu_pending_irq())
			goto out;

		/* Go to the retention state, the prcmu will wait for the
		 * cpu to go WFI and this is what happens after exiting this
		 * 'master' critical section */
		if (prcmu_set_power_state(PRCMU_AP_IDLE, true, true))
			goto out;

		/* When we switch to retention, the prcmu is in charge
		 * of recoupling the gic automatically */
		recouple = false;

		spin_unlock(&master_lock);
	}
wfi:
	cpu_do_idle();
out:
	atomic_dec(&master);

	if (recouple) {
		prcmu_gic_recouple();
		spin_unlock(&master_lock);
	}

	return index;
}