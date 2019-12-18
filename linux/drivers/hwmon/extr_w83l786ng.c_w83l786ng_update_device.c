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
struct w83l786ng_data {int valid; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int* fan_div; int* pwm_mode; int* pwm_enable; int* pwm; int** temp; int* tolerance; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int* W83L786NG_PWM_ENABLE_SHIFT ; 
 int* W83L786NG_PWM_MODE_SHIFT ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN (int) ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_CFG ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_DIV ; 
 int /*<<< orphan*/  W83L786NG_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  W83L786NG_REG_IN (int) ; 
 int /*<<< orphan*/  W83L786NG_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  W83L786NG_REG_IN_MIN (int) ; 
 int /*<<< orphan*/ * W83L786NG_REG_PWM ; 
 int /*<<< orphan*/ ** W83L786NG_REG_TEMP ; 
 int /*<<< orphan*/  W83L786NG_REG_TOLERANCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct w83l786ng_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int w83l786ng_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct w83l786ng_data *w83l786ng_update_device(struct device *dev)
{
	struct w83l786ng_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i, j;
	u8 reg_tmp, pwmcfg;

	mutex_lock(&data->update_lock);
	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		dev_dbg(&client->dev, "Updating w83l786ng data.\n");

		/* Update the voltages measured value and limits */
		for (i = 0; i < 3; i++) {
			data->in[i] = w83l786ng_read_value(client,
			    W83L786NG_REG_IN(i));
			data->in_min[i] = w83l786ng_read_value(client,
			    W83L786NG_REG_IN_MIN(i));
			data->in_max[i] = w83l786ng_read_value(client,
			    W83L786NG_REG_IN_MAX(i));
		}

		/* Update the fan counts and limits */
		for (i = 0; i < 2; i++) {
			data->fan[i] = w83l786ng_read_value(client,
			    W83L786NG_REG_FAN(i));
			data->fan_min[i] = w83l786ng_read_value(client,
			    W83L786NG_REG_FAN_MIN(i));
		}

		/* Update the fan divisor */
		reg_tmp = w83l786ng_read_value(client, W83L786NG_REG_FAN_DIV);
		data->fan_div[0] = reg_tmp & 0x07;
		data->fan_div[1] = (reg_tmp >> 4) & 0x07;

		pwmcfg = w83l786ng_read_value(client, W83L786NG_REG_FAN_CFG);
		for (i = 0; i < 2; i++) {
			data->pwm_mode[i] =
			    ((pwmcfg >> W83L786NG_PWM_MODE_SHIFT[i]) & 1)
			    ? 0 : 1;
			data->pwm_enable[i] =
			    ((pwmcfg >> W83L786NG_PWM_ENABLE_SHIFT[i]) & 3) + 1;
			data->pwm[i] =
			    (w83l786ng_read_value(client, W83L786NG_REG_PWM[i])
			     & 0x0f) * 0x11;
		}


		/* Update the temperature sensors */
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 3; j++) {
				data->temp[i][j] = w83l786ng_read_value(client,
				    W83L786NG_REG_TEMP[i][j]);
			}
		}

		/* Update Smart Fan I/II tolerance */
		reg_tmp = w83l786ng_read_value(client, W83L786NG_REG_TOLERANCE);
		data->tolerance[0] = reg_tmp & 0x0f;
		data->tolerance[1] = (reg_tmp >> 4) & 0x0f;

		data->last_updated = jiffies;
		data->valid = 1;

	}

	mutex_unlock(&data->update_lock);

	return data;
}