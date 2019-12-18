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
struct w83791d_data {int valid; int* in; int* in_max; int* in_min; int* fan; int* fan_min; int* fan_div; int* pwm; int* pwm_enable; int* temp_target; int* temp_tolerance; int* temp1; int** temp_add; int alarms; int beep_mask; int beep_enable; int vid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int GLOBAL_BEEP_ENABLE_SHIFT ; 
 int HZ ; 
 int NUMBER_OF_FANIN ; 
 int NUMBER_OF_PWM ; 
 int NUMBER_OF_VIN ; 
 int /*<<< orphan*/  W83791D_REG_ALARM1 ; 
 int /*<<< orphan*/  W83791D_REG_ALARM2 ; 
 int /*<<< orphan*/  W83791D_REG_ALARM3 ; 
 int /*<<< orphan*/ * W83791D_REG_BEEP_CTRL ; 
 int /*<<< orphan*/  W83791D_REG_DID_VID4 ; 
 int /*<<< orphan*/ * W83791D_REG_FAN ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_CFG ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_DIV ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_MIN ; 
 int /*<<< orphan*/ * W83791D_REG_IN ; 
 int /*<<< orphan*/ * W83791D_REG_IN_MAX ; 
 int /*<<< orphan*/ * W83791D_REG_IN_MIN ; 
 int /*<<< orphan*/ * W83791D_REG_PWM ; 
 int /*<<< orphan*/ * W83791D_REG_TEMP1 ; 
 int /*<<< orphan*/ ** W83791D_REG_TEMP_ADD ; 
 int /*<<< orphan*/ * W83791D_REG_TEMP_TARGET ; 
 int /*<<< orphan*/ * W83791D_REG_TEMP_TOL ; 
 int /*<<< orphan*/  W83791D_REG_VBAT ; 
 int /*<<< orphan*/  W83791D_REG_VID_FANDIV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct w83791d_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  w83791d_print_debug (struct w83791d_data*,struct device*) ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct w83791d_data *w83791d_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83791d_data *data = i2c_get_clientdata(client);
	int i, j;
	u8 reg_array_tmp[3];
	u8 vbat_reg;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + (HZ * 3))
			|| !data->valid) {
		dev_dbg(dev, "Starting w83791d device update\n");

		/* Update the voltages measured value and limits */
		for (i = 0; i < NUMBER_OF_VIN; i++) {
			data->in[i] = w83791d_read(client,
						W83791D_REG_IN[i]);
			data->in_max[i] = w83791d_read(client,
						W83791D_REG_IN_MAX[i]);
			data->in_min[i] = w83791d_read(client,
						W83791D_REG_IN_MIN[i]);
		}

		/* Update the fan counts and limits */
		for (i = 0; i < NUMBER_OF_FANIN; i++) {
			/* Update the Fan measured value and limits */
			data->fan[i] = w83791d_read(client,
						W83791D_REG_FAN[i]);
			data->fan_min[i] = w83791d_read(client,
						W83791D_REG_FAN_MIN[i]);
		}

		/* Update the fan divisor */
		for (i = 0; i < 3; i++) {
			reg_array_tmp[i] = w83791d_read(client,
						W83791D_REG_FAN_DIV[i]);
		}
		data->fan_div[0] = (reg_array_tmp[0] >> 4) & 0x03;
		data->fan_div[1] = (reg_array_tmp[0] >> 6) & 0x03;
		data->fan_div[2] = (reg_array_tmp[1] >> 6) & 0x03;
		data->fan_div[3] = reg_array_tmp[2] & 0x07;
		data->fan_div[4] = (reg_array_tmp[2] >> 4) & 0x07;

		/*
		 * The fan divisor for fans 0-2 get bit 2 from
		 * bits 5-7 respectively of vbat register
		 */
		vbat_reg = w83791d_read(client, W83791D_REG_VBAT);
		for (i = 0; i < 3; i++)
			data->fan_div[i] |= (vbat_reg >> (3 + i)) & 0x04;

		/* Update PWM duty cycle */
		for (i = 0; i < NUMBER_OF_PWM; i++) {
			data->pwm[i] =  w83791d_read(client,
						W83791D_REG_PWM[i]);
		}

		/* Update PWM enable status */
		for (i = 0; i < 2; i++) {
			reg_array_tmp[i] = w83791d_read(client,
						W83791D_REG_FAN_CFG[i]);
		}
		data->pwm_enable[0] = (reg_array_tmp[0] >> 2) & 0x03;
		data->pwm_enable[1] = (reg_array_tmp[0] >> 4) & 0x03;
		data->pwm_enable[2] = (reg_array_tmp[1] >> 2) & 0x03;

		/* Update PWM target temperature */
		for (i = 0; i < 3; i++) {
			data->temp_target[i] = w83791d_read(client,
				W83791D_REG_TEMP_TARGET[i]) & 0x7f;
		}

		/* Update PWM temperature tolerance */
		for (i = 0; i < 2; i++) {
			reg_array_tmp[i] = w83791d_read(client,
					W83791D_REG_TEMP_TOL[i]);
		}
		data->temp_tolerance[0] = reg_array_tmp[0] & 0x0f;
		data->temp_tolerance[1] = (reg_array_tmp[0] >> 4) & 0x0f;
		data->temp_tolerance[2] = reg_array_tmp[1] & 0x0f;

		/* Update the first temperature sensor */
		for (i = 0; i < 3; i++) {
			data->temp1[i] = w83791d_read(client,
						W83791D_REG_TEMP1[i]);
		}

		/* Update the rest of the temperature sensors */
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 3; j++) {
				data->temp_add[i][j] =
					(w83791d_read(client,
					W83791D_REG_TEMP_ADD[i][j * 2]) << 8) |
					w83791d_read(client,
					W83791D_REG_TEMP_ADD[i][j * 2 + 1]);
			}
		}

		/* Update the realtime status */
		data->alarms =
			w83791d_read(client, W83791D_REG_ALARM1) +
			(w83791d_read(client, W83791D_REG_ALARM2) << 8) +
			(w83791d_read(client, W83791D_REG_ALARM3) << 16);

		/* Update the beep configuration information */
		data->beep_mask =
			w83791d_read(client, W83791D_REG_BEEP_CTRL[0]) +
			(w83791d_read(client, W83791D_REG_BEEP_CTRL[1]) << 8) +
			(w83791d_read(client, W83791D_REG_BEEP_CTRL[2]) << 16);

		/* Extract global beep enable flag */
		data->beep_enable =
			(data->beep_mask >> GLOBAL_BEEP_ENABLE_SHIFT) & 0x01;

		/* Update the cpu voltage information */
		i = w83791d_read(client, W83791D_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (w83791d_read(client, W83791D_REG_DID_VID4) & 0x01)
				<< 4;

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

#ifdef DEBUG
	w83791d_print_debug(data, dev);
#endif

	return data;
}