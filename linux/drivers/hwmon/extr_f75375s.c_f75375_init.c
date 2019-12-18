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
struct i2c_client {int dummy; } ;
struct f75375s_platform_data {int /*<<< orphan*/ * pwm; int /*<<< orphan*/ * pwm_enable; } ;
struct f75375_data {scalar_t__ kind; int* pwm_mode; int* pwm_enable; int /*<<< orphan*/ * pwm; } ;

/* Variables and functions */
 int F75375_FAN_CTRL_LINEAR (int) ; 
 int /*<<< orphan*/  F75375_REG_CONFIG1 ; 
 int /*<<< orphan*/  F75375_REG_FAN_TIMER ; 
 int F75387_FAN_CTRL_LINEAR (int) ; 
 int F75387_FAN_DUTY_MODE (int) ; 
 int F75387_FAN_MANU_MODE (int) ; 
 int FAN_CTRL_MODE (int) ; 
 scalar_t__ auto_mode_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  duty_mode_enabled (int /*<<< orphan*/ ) ; 
 int f75375_read8 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_write_pwm (struct i2c_client*,int) ; 
 scalar_t__ f75387 ; 
 int /*<<< orphan*/  set_pwm_enable_direct (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f75375_init(struct i2c_client *client, struct f75375_data *data,
		struct f75375s_platform_data *f75375s_pdata)
{
	int nr;

	if (!f75375s_pdata) {
		u8 conf, mode;
		int nr;

		conf = f75375_read8(client, F75375_REG_CONFIG1);
		mode = f75375_read8(client, F75375_REG_FAN_TIMER);
		for (nr = 0; nr < 2; nr++) {
			if (data->kind == f75387) {
				bool manu, duty;

				if (!(mode & (1 << F75387_FAN_CTRL_LINEAR(nr))))
					data->pwm_mode[nr] = 1;

				manu = ((mode >> F75387_FAN_MANU_MODE(nr)) & 1);
				duty = ((mode >> F75387_FAN_DUTY_MODE(nr)) & 1);
				if (!manu && duty)
					/* auto, pwm */
					data->pwm_enable[nr] = 4;
				else if (manu && !duty)
					/* manual, speed */
					data->pwm_enable[nr] = 3;
				else if (!manu && !duty)
					/* automatic, speed */
					data->pwm_enable[nr] = 2;
				else
					/* manual, pwm */
					data->pwm_enable[nr] = 1;
			} else {
				if (!(conf & (1 << F75375_FAN_CTRL_LINEAR(nr))))
					data->pwm_mode[nr] = 1;

				switch ((mode >> FAN_CTRL_MODE(nr)) & 3) {
				case 0:		/* speed */
					data->pwm_enable[nr] = 3;
					break;
				case 1:		/* automatic */
					data->pwm_enable[nr] = 2;
					break;
				default:	/* manual */
					data->pwm_enable[nr] = 1;
					break;
				}
			}
		}
		return;
	}

	set_pwm_enable_direct(client, 0, f75375s_pdata->pwm_enable[0]);
	set_pwm_enable_direct(client, 1, f75375s_pdata->pwm_enable[1]);
	for (nr = 0; nr < 2; nr++) {
		if (auto_mode_enabled(f75375s_pdata->pwm_enable[nr]) ||
		    !duty_mode_enabled(f75375s_pdata->pwm_enable[nr]))
			continue;
		data->pwm[nr] = clamp_val(f75375s_pdata->pwm[nr], 0, 255);
		f75375_write_pwm(client, nr);
	}

}