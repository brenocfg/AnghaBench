#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int connected; int /*<<< orphan*/  reg; } ;
struct mlxreg_fan {int* cooling_levels; int /*<<< orphan*/  dev; scalar_t__ divider; scalar_t__ samples; TYPE_2__ pwm; TYPE_1__* tacho; } ;
struct mlxreg_core_platform_data {int counter; struct mlxreg_core_data* data; } ;
struct mlxreg_core_data {int /*<<< orphan*/  label; scalar_t__ bit; scalar_t__ mask; scalar_t__ capability; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int connected; scalar_t__ mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLXREG_FAN_MAX_STATE ; 
 int MLXREG_FAN_MAX_TACHO ; 
 int MLXREG_FAN_SPEED_MIN_LEVEL ; 
 scalar_t__ MLXREG_FAN_TACHO_DIV_DEF ; 
 scalar_t__ MLXREG_FAN_TACHO_SAMPLES_PER_PULSE_DEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mlxreg_fan_connect_verify (struct mlxreg_fan*,struct mlxreg_core_data*) ; 
 int mlxreg_fan_speed_divider_get (struct mlxreg_fan*,struct mlxreg_core_data*) ; 
 scalar_t__ strnstr (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mlxreg_fan_config(struct mlxreg_fan *fan,
			     struct mlxreg_core_platform_data *pdata)
{
	struct mlxreg_core_data *data = pdata->data;
	bool configured = false;
	int tacho_num = 0, i;
	int err;

	fan->samples = MLXREG_FAN_TACHO_SAMPLES_PER_PULSE_DEF;
	fan->divider = MLXREG_FAN_TACHO_DIV_DEF;
	for (i = 0; i < pdata->counter; i++, data++) {
		if (strnstr(data->label, "tacho", sizeof(data->label))) {
			if (tacho_num == MLXREG_FAN_MAX_TACHO) {
				dev_err(fan->dev, "too many tacho entries: %s\n",
					data->label);
				return -EINVAL;
			}

			if (data->capability) {
				err = mlxreg_fan_connect_verify(fan, data);
				if (err < 0)
					return err;
				else if (!err) {
					tacho_num++;
					continue;
				}
			}

			fan->tacho[tacho_num].reg = data->reg;
			fan->tacho[tacho_num].mask = data->mask;
			fan->tacho[tacho_num++].connected = true;
		} else if (strnstr(data->label, "pwm", sizeof(data->label))) {
			if (fan->pwm.connected) {
				dev_err(fan->dev, "duplicate pwm entry: %s\n",
					data->label);
				return -EINVAL;
			}
			fan->pwm.reg = data->reg;
			fan->pwm.connected = true;
		} else if (strnstr(data->label, "conf", sizeof(data->label))) {
			if (configured) {
				dev_err(fan->dev, "duplicate conf entry: %s\n",
					data->label);
				return -EINVAL;
			}
			/* Validate that conf parameters are not zeros. */
			if (!data->mask && !data->bit && !data->capability) {
				dev_err(fan->dev, "invalid conf entry params: %s\n",
					data->label);
				return -EINVAL;
			}
			if (data->capability) {
				err = mlxreg_fan_speed_divider_get(fan, data);
				if (err)
					return err;
			} else {
				if (data->mask)
					fan->samples = data->mask;
				if (data->bit)
					fan->divider = data->bit;
			}
			configured = true;
		} else {
			dev_err(fan->dev, "invalid label: %s\n", data->label);
			return -EINVAL;
		}
	}

	/* Init cooling levels per PWM state. */
	for (i = 0; i < MLXREG_FAN_SPEED_MIN_LEVEL; i++)
		fan->cooling_levels[i] = MLXREG_FAN_SPEED_MIN_LEVEL;
	for (i = MLXREG_FAN_SPEED_MIN_LEVEL; i <= MLXREG_FAN_MAX_STATE; i++)
		fan->cooling_levels[i] = i;

	return 0;
}