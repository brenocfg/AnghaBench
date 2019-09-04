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
struct vt1211_data {int valid; int vid; int* in; int* in_min; int* in_max; int* temp; int* temp_max; int* temp_hyst; int* fan; int* fan_min; int* pwm; int* fan_div; int fan_ctl; int* pwm_ctl; int pwm_clk; int** pwm_auto_pwm; int* pwm_auto_temp; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/  uch_config; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ HZ ; 
 scalar_t__ ISTEMP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ISVOLT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT1211_REG_ALARM1 ; 
 int /*<<< orphan*/  VT1211_REG_ALARM2 ; 
 int /*<<< orphan*/  VT1211_REG_FAN (int) ; 
 int /*<<< orphan*/  VT1211_REG_FAN_DIV ; 
 int /*<<< orphan*/  VT1211_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  VT1211_REG_IN (int) ; 
 int /*<<< orphan*/  VT1211_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  VT1211_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  VT1211_REG_PWM (int) ; 
 int /*<<< orphan*/  VT1211_REG_PWM_AUTO_PWM (int,int) ; 
 int /*<<< orphan*/  VT1211_REG_PWM_AUTO_TEMP (int) ; 
 int /*<<< orphan*/  VT1211_REG_PWM_CLK ; 
 int /*<<< orphan*/  VT1211_REG_PWM_CTL ; 
 int /*<<< orphan*/  VT1211_REG_VID ; 
 struct vt1211_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regtemp ; 
 int /*<<< orphan*/ * regtemphyst ; 
 int /*<<< orphan*/ * regtempmax ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int vt1211_read8 (struct vt1211_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vt1211_data *vt1211_update_device(struct device *dev)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	int ix, val;

	mutex_lock(&data->update_lock);

	/* registers cache is refreshed after 1 second */
	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		/* read VID */
		data->vid = vt1211_read8(data, VT1211_REG_VID) & 0x1f;

		/* voltage (in) registers */
		for (ix = 0; ix < ARRAY_SIZE(data->in); ix++) {
			if (ISVOLT(ix, data->uch_config)) {
				data->in[ix] = vt1211_read8(data,
						VT1211_REG_IN(ix));
				data->in_min[ix] = vt1211_read8(data,
						VT1211_REG_IN_MIN(ix));
				data->in_max[ix] = vt1211_read8(data,
						VT1211_REG_IN_MAX(ix));
			}
		}

		/* temp registers */
		for (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) {
			if (ISTEMP(ix, data->uch_config)) {
				data->temp[ix] = vt1211_read8(data,
						regtemp[ix]);
				data->temp_max[ix] = vt1211_read8(data,
						regtempmax[ix]);
				data->temp_hyst[ix] = vt1211_read8(data,
						regtemphyst[ix]);
			}
		}

		/* fan & pwm registers */
		for (ix = 0; ix < ARRAY_SIZE(data->fan); ix++) {
			data->fan[ix] = vt1211_read8(data,
						VT1211_REG_FAN(ix));
			data->fan_min[ix] = vt1211_read8(data,
						VT1211_REG_FAN_MIN(ix));
			data->pwm[ix] = vt1211_read8(data,
						VT1211_REG_PWM(ix));
		}
		val = vt1211_read8(data, VT1211_REG_FAN_DIV);
		data->fan_div[0] = (val >> 4) & 3;
		data->fan_div[1] = (val >> 6) & 3;
		data->fan_ctl = val & 0xf;

		val = vt1211_read8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = val & 0xf;
		data->pwm_ctl[1] = (val >> 4) & 0xf;

		data->pwm_clk = vt1211_read8(data, VT1211_REG_PWM_CLK);

		/* pwm & temp auto point registers */
		data->pwm_auto_pwm[0][1] = vt1211_read8(data,
						VT1211_REG_PWM_AUTO_PWM(0, 1));
		data->pwm_auto_pwm[0][2] = vt1211_read8(data,
						VT1211_REG_PWM_AUTO_PWM(0, 2));
		data->pwm_auto_pwm[1][1] = vt1211_read8(data,
						VT1211_REG_PWM_AUTO_PWM(1, 1));
		data->pwm_auto_pwm[1][2] = vt1211_read8(data,
						VT1211_REG_PWM_AUTO_PWM(1, 2));
		for (ix = 0; ix < ARRAY_SIZE(data->pwm_auto_temp); ix++) {
			data->pwm_auto_temp[ix] = vt1211_read8(data,
						VT1211_REG_PWM_AUTO_TEMP(ix));
		}

		/* alarm registers */
		data->alarms = (vt1211_read8(data, VT1211_REG_ALARM2) << 8) |
				vt1211_read8(data, VT1211_REG_ALARM1);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}