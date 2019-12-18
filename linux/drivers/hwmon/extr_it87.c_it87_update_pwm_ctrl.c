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
struct it87_data {int* pwm_ctrl; int* pwm_temp_map; int* pwm_duty; void*** auto_pwm; void*** auto_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT87_REG_AUTO_PWM (int,int) ; 
 int /*<<< orphan*/  IT87_REG_AUTO_TEMP (int,int) ; 
 int /*<<< orphan*/ * IT87_REG_PWM ; 
 int /*<<< orphan*/ * IT87_REG_PWM_DUTY ; 
 scalar_t__ has_newer_autopwm (struct it87_data*) ; 
 scalar_t__ has_old_autopwm (struct it87_data*) ; 
 void* it87_read_value (struct it87_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it87_update_pwm_ctrl(struct it87_data *data, int nr)
{
	data->pwm_ctrl[nr] = it87_read_value(data, IT87_REG_PWM[nr]);
	if (has_newer_autopwm(data)) {
		data->pwm_temp_map[nr] = data->pwm_ctrl[nr] & 0x03;
		data->pwm_duty[nr] = it87_read_value(data,
						     IT87_REG_PWM_DUTY[nr]);
	} else {
		if (data->pwm_ctrl[nr] & 0x80)	/* Automatic mode */
			data->pwm_temp_map[nr] = data->pwm_ctrl[nr] & 0x03;
		else				/* Manual mode */
			data->pwm_duty[nr] = data->pwm_ctrl[nr] & 0x7f;
	}

	if (has_old_autopwm(data)) {
		int i;

		for (i = 0; i < 5 ; i++)
			data->auto_temp[nr][i] = it87_read_value(data,
						IT87_REG_AUTO_TEMP(nr, i));
		for (i = 0; i < 3 ; i++)
			data->auto_pwm[nr][i] = it87_read_value(data,
						IT87_REG_AUTO_PWM(nr, i));
	} else if (has_newer_autopwm(data)) {
		int i;

		/*
		 * 0: temperature hysteresis (base + 5)
		 * 1: fan off temperature (base + 0)
		 * 2: fan start temperature (base + 1)
		 * 3: fan max temperature (base + 2)
		 */
		data->auto_temp[nr][0] =
			it87_read_value(data, IT87_REG_AUTO_TEMP(nr, 5));

		for (i = 0; i < 3 ; i++)
			data->auto_temp[nr][i + 1] =
				it87_read_value(data,
						IT87_REG_AUTO_TEMP(nr, i));
		/*
		 * 0: start pwm value (base + 3)
		 * 1: pwm slope (base + 4, 1/8th pwm)
		 */
		data->auto_pwm[nr][0] =
			it87_read_value(data, IT87_REG_AUTO_TEMP(nr, 3));
		data->auto_pwm[nr][1] =
			it87_read_value(data, IT87_REG_AUTO_TEMP(nr, 4));
	}
}