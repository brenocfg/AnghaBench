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
typedef  int u8 ;
struct pwm_device {int hwpwm; int /*<<< orphan*/  label; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  TWL_MODULE_PWM ; 
 int TWL_PWM_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write (int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int twl_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			      int duty_ns, int period_ns)
{
	int duty_cycle = DIV_ROUND_UP(duty_ns * TWL_PWM_MAX, period_ns) + 1;
	u8 pwm_config[2] = { 1, 0 };
	int base, ret;

	/*
	 * To configure the duty period:
	 * On-cycle is set to 1 (the minimum allowed value)
	 * The off time of 0 is not configurable, so the mapping is:
	 * 0 -> off cycle = 2,
	 * 1 -> off cycle = 2,
	 * 2 -> off cycle = 3,
	 * 126 - > off cycle 127,
	 * 127 - > off cycle 1
	 * When on cycle == off cycle the PWM will be always on
	 */
	if (duty_cycle == 1)
		duty_cycle = 2;
	else if (duty_cycle > TWL_PWM_MAX)
		duty_cycle = 1;

	base = pwm->hwpwm * 3;

	pwm_config[1] = duty_cycle;

	ret = twl_i2c_write(TWL_MODULE_PWM, pwm_config, base, 2);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to configure PWM\n", pwm->label);

	return ret;
}