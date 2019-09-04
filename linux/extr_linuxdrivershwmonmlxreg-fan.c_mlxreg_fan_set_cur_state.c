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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_cooling_device {struct mlxreg_fan* devdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct mlxreg_fan {unsigned long* cooling_levels; int /*<<< orphan*/  dev; TYPE_1__ pwm; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MLXREG_FAN_MAX_STATE ; 
 unsigned long MLXREG_FAN_PWM_DUTY2STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXREG_FAN_PWM_STATE2DUTY (unsigned long) ; 
 unsigned long MLXREG_FAN_SPEED_MAX ; 
 unsigned long MLXREG_FAN_SPEED_MIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxreg_fan_set_cur_state(struct thermal_cooling_device *cdev,
				    unsigned long state)

{
	struct mlxreg_fan *fan = cdev->devdata;
	unsigned long cur_state;
	u32 regval;
	int i;
	int err;

	/*
	 * Verify if this request is for changing allowed FAN dynamical
	 * minimum. If it is - update cooling levels accordingly and update
	 * state, if current state is below the newly requested minimum state.
	 * For example, if current state is 5, and minimal state is to be
	 * changed from 4 to 6, fan->cooling_levels[0 to 5] will be changed all
	 * from 4 to 6. And state 5 (fan->cooling_levels[4]) should be
	 * overwritten.
	 */
	if (state >= MLXREG_FAN_SPEED_MIN && state <= MLXREG_FAN_SPEED_MAX) {
		state -= MLXREG_FAN_MAX_STATE;
		for (i = 0; i < state; i++)
			fan->cooling_levels[i] = state;
		for (i = state; i <= MLXREG_FAN_MAX_STATE; i++)
			fan->cooling_levels[i] = i;

		err = regmap_read(fan->regmap, fan->pwm.reg, &regval);
		if (err) {
			dev_err(fan->dev, "Failed to query PWM duty\n");
			return err;
		}

		cur_state = MLXREG_FAN_PWM_DUTY2STATE(regval);
		if (state < cur_state)
			return 0;

		state = cur_state;
	}

	if (state > MLXREG_FAN_MAX_STATE)
		return -EINVAL;

	/* Normalize the state to the valid speed range. */
	state = fan->cooling_levels[state];
	err = regmap_write(fan->regmap, fan->pwm.reg,
			   MLXREG_FAN_PWM_STATE2DUTY(state));
	if (err) {
		dev_err(fan->dev, "Failed to write PWM duty\n");
		return err;
	}
	return 0;
}