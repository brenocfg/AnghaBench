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
struct idle_statedata {scalar_t__ mpu_state_vote; int /*<<< orphan*/  cpu_state; int /*<<< orphan*/  mpu_state; int /*<<< orphan*/  mpu_logic_state; } ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRDM_POWER_ON ; 
 int /*<<< orphan*/  mpu_lock ; 
 int /*<<< orphan*/  mpu_pd ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  omap4_enter_lowpower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_pwrdm_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_logic_retst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idle_statedata* state_ptr ; 

__attribute__((used)) static int omap_enter_idle_smp(struct cpuidle_device *dev,
			       struct cpuidle_driver *drv,
			       int index)
{
	struct idle_statedata *cx = state_ptr + index;
	unsigned long flag;

	raw_spin_lock_irqsave(&mpu_lock, flag);
	cx->mpu_state_vote++;
	if (cx->mpu_state_vote == num_online_cpus()) {
		pwrdm_set_logic_retst(mpu_pd, cx->mpu_logic_state);
		omap_set_pwrdm_state(mpu_pd, cx->mpu_state);
	}
	raw_spin_unlock_irqrestore(&mpu_lock, flag);

	omap4_enter_lowpower(dev->cpu, cx->cpu_state);

	raw_spin_lock_irqsave(&mpu_lock, flag);
	if (cx->mpu_state_vote == num_online_cpus())
		omap_set_pwrdm_state(mpu_pd, PWRDM_POWER_ON);
	cx->mpu_state_vote--;
	raw_spin_unlock_irqrestore(&mpu_lock, flag);

	return index;
}