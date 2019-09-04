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
struct cpuidle_device {int /*<<< orphan*/  cpu; } ;
typedef  enum cps_pm_state { ____Placeholder_cps_pm_state } cps_pm_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CPS_PM_CLOCK_GATED ; 
 int CPS_PM_NC_WAIT ; 
 int CPS_PM_POWER_GATED ; 
 int EINTR ; 
 int EINVAL ; 
#define  STATE_CLOCK_GATED 130 
#define  STATE_NC_WAIT 129 
#define  STATE_POWER_GATED 128 
 int cps_pm_enter_state (int) ; 
 scalar_t__ cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 scalar_t__ cpus_are_siblings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cps_nc_enter(struct cpuidle_device *dev,
			struct cpuidle_driver *drv, int index)
{
	enum cps_pm_state pm_state;
	int err;

	/*
	 * At least one core must remain powered up & clocked in order for the
	 * system to have any hope of functioning.
	 *
	 * TODO: don't treat core 0 specially, just prevent the final core
	 * TODO: remap interrupt affinity temporarily
	 */
	if (cpus_are_siblings(0, dev->cpu) && (index > STATE_NC_WAIT))
		index = STATE_NC_WAIT;

	/* Select the appropriate cps_pm_state */
	switch (index) {
	case STATE_NC_WAIT:
		pm_state = CPS_PM_NC_WAIT;
		break;
	case STATE_CLOCK_GATED:
		pm_state = CPS_PM_CLOCK_GATED;
		break;
	case STATE_POWER_GATED:
		pm_state = CPS_PM_POWER_GATED;
		break;
	default:
		BUG();
		return -EINVAL;
	}

	/* Notify listeners the CPU is about to power down */
	if ((pm_state == CPS_PM_POWER_GATED) && cpu_pm_enter())
		return -EINTR;

	/* Enter that state */
	err = cps_pm_enter_state(pm_state);

	/* Notify listeners the CPU is back up */
	if (pm_state == CPS_PM_POWER_GATED)
		cpu_pm_exit();

	return err ?: index;
}