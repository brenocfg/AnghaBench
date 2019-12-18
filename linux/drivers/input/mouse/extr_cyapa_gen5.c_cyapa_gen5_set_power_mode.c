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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct device {int dummy; } ;
struct cyapa {scalar_t__ state; int /*<<< orphan*/  dev_sleep_time; TYPE_1__* client; } ;
typedef  enum cyapa_pm_stage { ____Placeholder_cyapa_pm_stage } cyapa_pm_stage ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int CYAPA_PM_SUSPEND ; 
 scalar_t__ CYAPA_STATE_GEN5_APP ; 
 int /*<<< orphan*/  GEN5_PARAMETER_LP_INTRVL_ID ; 
 scalar_t__ GEN5_POWER_READY_MAX_INTRVL_TIME ; 
 scalar_t__ GEN5_POWER_STATE_ACTIVE ; 
 scalar_t__ GEN5_POWER_STATE_BTN_ONLY ; 
 scalar_t__ GEN5_POWER_STATE_IDLE ; 
 scalar_t__ GEN5_POWER_STATE_READY ; 
 int /*<<< orphan*/  PIP_DEEP_SLEEP_STATE_OFF ; 
 int /*<<< orphan*/  PIP_DEEP_SLEEP_STATE_ON ; 
 scalar_t__ PIP_DEV_GET_PWR_STATE (struct cyapa*) ; 
 scalar_t__ PIP_DEV_GET_SLEEP_TIME (struct cyapa*) ; 
 int /*<<< orphan*/  PIP_DEV_SET_PWR_STATE (struct cyapa*,scalar_t__) ; 
 int /*<<< orphan*/  PIP_DEV_SET_SLEEP_TIME (struct cyapa*,scalar_t__) ; 
 scalar_t__ PIP_DEV_UNINIT_SLEEP_TIME (struct cyapa*) ; 
 scalar_t__ PWR_MODE_BTN_ONLY ; 
 scalar_t__ PWR_MODE_FULL_ACTIVE ; 
 scalar_t__ PWR_MODE_OFF ; 
 scalar_t__ UNINIT_PWR_MODE ; 
 scalar_t__ UNINIT_SLEEP_TIME ; 
 int cyapa_gen5_change_power_state (struct cyapa*,scalar_t__) ; 
 int /*<<< orphan*/  cyapa_gen5_disable_pip_report (struct cyapa*) ; 
 scalar_t__ cyapa_gen5_get_interval_time (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cyapa_gen5_set_interval_time (struct cyapa*,int /*<<< orphan*/ ,scalar_t__) ; 
 int cyapa_pip_deep_sleep (struct cyapa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyapa_reset_pip_pm_state (struct cyapa*) ; 
 int /*<<< orphan*/  cyapa_set_pip_pm_state (struct cyapa*,int) ; 
 scalar_t__ cyapa_sleep_time_to_pwr_cmd (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 

__attribute__((used)) static int cyapa_gen5_set_power_mode(struct cyapa *cyapa,
		u8 power_mode, u16 sleep_time, enum cyapa_pm_stage pm_stage)
{
	struct device *dev = &cyapa->client->dev;
	u8 power_state;
	int error = 0;

	if (cyapa->state != CYAPA_STATE_GEN5_APP)
		return 0;

	cyapa_set_pip_pm_state(cyapa, pm_stage);

	if (PIP_DEV_GET_PWR_STATE(cyapa) == UNINIT_PWR_MODE) {
		/*
		 * Assume TP in deep sleep mode when driver is loaded,
		 * avoid driver unload and reload command IO issue caused by TP
		 * has been set into deep sleep mode when unloading.
		 */
		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_OFF);
	}

	if (PIP_DEV_UNINIT_SLEEP_TIME(cyapa) &&
			PIP_DEV_GET_PWR_STATE(cyapa) != PWR_MODE_OFF)
		if (cyapa_gen5_get_interval_time(cyapa,
				GEN5_PARAMETER_LP_INTRVL_ID,
				&cyapa->dev_sleep_time) != 0)
			PIP_DEV_SET_SLEEP_TIME(cyapa, UNINIT_SLEEP_TIME);

	if (PIP_DEV_GET_PWR_STATE(cyapa) == power_mode) {
		if (power_mode == PWR_MODE_OFF ||
			power_mode == PWR_MODE_FULL_ACTIVE ||
			power_mode == PWR_MODE_BTN_ONLY ||
			PIP_DEV_GET_SLEEP_TIME(cyapa) == sleep_time) {
			/* Has in correct power mode state, early return. */
			goto out;
		}
	}

	if (power_mode == PWR_MODE_OFF) {
		error = cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_OFF);
		if (error) {
			dev_err(dev, "enter deep sleep fail: %d\n", error);
			goto out;
		}

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_OFF);
		goto out;
	}

	/*
	 * When trackpad in power off mode, it cannot change to other power
	 * state directly, must be wake up from sleep firstly, then
	 * continue to do next power sate change.
	 */
	if (PIP_DEV_GET_PWR_STATE(cyapa) == PWR_MODE_OFF) {
		error = cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);
		if (error) {
			dev_err(dev, "deep sleep wake fail: %d\n", error);
			goto out;
		}
	}

	if (power_mode == PWR_MODE_FULL_ACTIVE) {
		error = cyapa_gen5_change_power_state(cyapa,
				GEN5_POWER_STATE_ACTIVE);
		if (error) {
			dev_err(dev, "change to active fail: %d\n", error);
			goto out;
		}

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_FULL_ACTIVE);
	} else if (power_mode == PWR_MODE_BTN_ONLY) {
		error = cyapa_gen5_change_power_state(cyapa,
				GEN5_POWER_STATE_BTN_ONLY);
		if (error) {
			dev_err(dev, "fail to button only mode: %d\n", error);
			goto out;
		}

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_BTN_ONLY);
	} else {
		/*
		 * Continue to change power mode even failed to set
		 * interval time, it won't affect the power mode change.
		 * except the sleep interval time is not correct.
		 */
		if (PIP_DEV_UNINIT_SLEEP_TIME(cyapa) ||
				sleep_time != PIP_DEV_GET_SLEEP_TIME(cyapa))
			if (cyapa_gen5_set_interval_time(cyapa,
					GEN5_PARAMETER_LP_INTRVL_ID,
					sleep_time) == 0)
				PIP_DEV_SET_SLEEP_TIME(cyapa, sleep_time);

		if (sleep_time <= GEN5_POWER_READY_MAX_INTRVL_TIME)
			power_state = GEN5_POWER_STATE_READY;
		else
			power_state = GEN5_POWER_STATE_IDLE;
		error = cyapa_gen5_change_power_state(cyapa, power_state);
		if (error) {
			dev_err(dev, "set power state to 0x%02x failed: %d\n",
				power_state, error);
			goto out;
		}

		/*
		 * Disable pip report for a little time, firmware will
		 * re-enable it automatically. It's used to fix the issue
		 * that trackpad unable to report signal to wake system up
		 * in the special situation that system is in suspending, and
		 * at the same time, user touch trackpad to wake system up.
		 * This function can avoid the data to be buffered when system
		 * is suspending which may cause interrupt line unable to be
		 * asserted again.
		 */
		if (pm_stage == CYAPA_PM_SUSPEND)
			cyapa_gen5_disable_pip_report(cyapa);

		PIP_DEV_SET_PWR_STATE(cyapa,
			cyapa_sleep_time_to_pwr_cmd(sleep_time));
	}

out:
	cyapa_reset_pip_pm_state(cyapa);
	return error;
}