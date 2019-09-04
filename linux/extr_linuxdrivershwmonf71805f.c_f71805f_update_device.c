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
struct f71805f_data {int valid; int has_in; int* in_high; int* in_low; int* pwm_freq; int* temp_high; int* temp_hyst; int temp_mode; int* in; int* fan_ctrl; int* pwm; int* temp; int /*<<< orphan*/  update_lock; void* last_updated; scalar_t__ alarms; void** fan; void* last_limits; TYPE_1__* auto_points; void** fan_target; void** fan_low; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int* temp; void** fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71805F_REG_FAN (int) ; 
 int /*<<< orphan*/  F71805F_REG_FAN_CTRL (int) ; 
 int /*<<< orphan*/  F71805F_REG_FAN_LOW (int) ; 
 int /*<<< orphan*/  F71805F_REG_FAN_TARGET (int) ; 
 int /*<<< orphan*/  F71805F_REG_IN (int) ; 
 int /*<<< orphan*/  F71805F_REG_IN_HIGH (int) ; 
 int /*<<< orphan*/  F71805F_REG_IN_LOW (int) ; 
 int /*<<< orphan*/  F71805F_REG_PWM_AUTO_POINT_FAN (int,int) ; 
 int /*<<< orphan*/  F71805F_REG_PWM_AUTO_POINT_TEMP (int,int) ; 
 int /*<<< orphan*/  F71805F_REG_PWM_DUTY (int) ; 
 int /*<<< orphan*/  F71805F_REG_PWM_FREQ (int) ; 
 int /*<<< orphan*/  F71805F_REG_STATUS (int) ; 
 int /*<<< orphan*/  F71805F_REG_TEMP (int) ; 
 int /*<<< orphan*/  F71805F_REG_TEMP_HIGH (int) ; 
 int /*<<< orphan*/  F71805F_REG_TEMP_HYST (int) ; 
 int /*<<< orphan*/  F71805F_REG_TEMP_MODE ; 
 int HZ ; 
 struct f71805f_data* dev_get_drvdata (struct device*) ; 
 void* f71805f_read16 (struct f71805f_data*,int /*<<< orphan*/ ) ; 
 int f71805f_read8 (struct f71805f_data*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (void*,void*) ; 

__attribute__((used)) static struct f71805f_data *f71805f_update_device(struct device *dev)
{
	struct f71805f_data *data = dev_get_drvdata(dev);
	int nr, apnr;

	mutex_lock(&data->update_lock);

	/* Limit registers cache is refreshed after 60 seconds */
	if (time_after(jiffies, data->last_updated + 60 * HZ)
	 || !data->valid) {
		for (nr = 0; nr < 11; nr++) {
			if (!(data->has_in & (1 << nr)))
				continue;
			data->in_high[nr] = f71805f_read8(data,
					    F71805F_REG_IN_HIGH(nr));
			data->in_low[nr] = f71805f_read8(data,
					   F71805F_REG_IN_LOW(nr));
		}
		for (nr = 0; nr < 3; nr++) {
			data->fan_low[nr] = f71805f_read16(data,
					    F71805F_REG_FAN_LOW(nr));
			data->fan_target[nr] = f71805f_read16(data,
					       F71805F_REG_FAN_TARGET(nr));
			data->pwm_freq[nr] = f71805f_read8(data,
					     F71805F_REG_PWM_FREQ(nr));
		}
		for (nr = 0; nr < 3; nr++) {
			data->temp_high[nr] = f71805f_read8(data,
					      F71805F_REG_TEMP_HIGH(nr));
			data->temp_hyst[nr] = f71805f_read8(data,
					      F71805F_REG_TEMP_HYST(nr));
		}
		data->temp_mode = f71805f_read8(data, F71805F_REG_TEMP_MODE);
		for (nr = 0; nr < 3; nr++) {
			for (apnr = 0; apnr < 3; apnr++) {
				data->auto_points[nr].temp[apnr] =
					f71805f_read8(data,
					F71805F_REG_PWM_AUTO_POINT_TEMP(nr,
									apnr));
				data->auto_points[nr].fan[apnr] =
					f71805f_read16(data,
					F71805F_REG_PWM_AUTO_POINT_FAN(nr,
								       apnr));
			}
		}

		data->last_limits = jiffies;
	}

	/* Measurement registers cache is refreshed after 1 second */
	if (time_after(jiffies, data->last_updated + HZ)
	 || !data->valid) {
		for (nr = 0; nr < 11; nr++) {
			if (!(data->has_in & (1 << nr)))
				continue;
			data->in[nr] = f71805f_read8(data,
				       F71805F_REG_IN(nr));
		}
		for (nr = 0; nr < 3; nr++) {
			data->fan[nr] = f71805f_read16(data,
					F71805F_REG_FAN(nr));
			data->fan_ctrl[nr] = f71805f_read8(data,
					     F71805F_REG_FAN_CTRL(nr));
			data->pwm[nr] = f71805f_read8(data,
					F71805F_REG_PWM_DUTY(nr));
		}
		for (nr = 0; nr < 3; nr++) {
			data->temp[nr] = f71805f_read8(data,
					 F71805F_REG_TEMP(nr));
		}
		data->alarms = f71805f_read8(data, F71805F_REG_STATUS(0))
			+ (f71805f_read8(data, F71805F_REG_STATUS(1)) << 8)
			+ (f71805f_read8(data, F71805F_REG_STATUS(2)) << 16);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}