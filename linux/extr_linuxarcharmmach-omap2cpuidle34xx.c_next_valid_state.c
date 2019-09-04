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
typedef  scalar_t__ u32 ;
struct omap3_idle_statedata {scalar_t__ mpu_state; scalar_t__ core_state; } ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PM34XX_ERRATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_SDRC_WAKEUP_ERRATUM_i583 ; 
 scalar_t__ PWRDM_POWER_OFF ; 
 scalar_t__ PWRDM_POWER_RET ; 
 scalar_t__ enable_off_mode ; 
 struct omap3_idle_statedata* omap3_idle_data ; 

__attribute__((used)) static int next_valid_state(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv, int index)
{
	struct omap3_idle_statedata *cx = &omap3_idle_data[index];
	u32 mpu_deepest_state = PWRDM_POWER_RET;
	u32 core_deepest_state = PWRDM_POWER_RET;
	int idx;
	int next_index = 0; /* C1 is the default value */

	if (enable_off_mode) {
		mpu_deepest_state = PWRDM_POWER_OFF;
		/*
		 * Erratum i583: valable for ES rev < Es1.2 on 3630.
		 * CORE OFF mode is not supported in a stable form, restrict
		 * instead the CORE state to RET.
		 */
		if (!IS_PM34XX_ERRATUM(PM_SDRC_WAKEUP_ERRATUM_i583))
			core_deepest_state = PWRDM_POWER_OFF;
	}

	/* Check if current state is valid */
	if ((cx->mpu_state >= mpu_deepest_state) &&
	    (cx->core_state >= core_deepest_state))
		return index;

	/*
	 * Drop to next valid state.
	 * Start search from the next (lower) state.
	 */
	for (idx = index - 1; idx >= 0; idx--) {
		cx = &omap3_idle_data[idx];
		if ((cx->mpu_state >= mpu_deepest_state) &&
		    (cx->core_state >= core_deepest_state)) {
			next_index = idx;
			break;
		}
	}

	return next_index;
}