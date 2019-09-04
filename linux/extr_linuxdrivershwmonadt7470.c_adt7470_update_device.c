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
struct device {int dummy; } ;
struct adt7470_data {unsigned long sensors_last_updated; int sensors_valid; unsigned long limits_last_updated; int limits_valid; int* temp; int* pwm; int* pwm_automatic; int* pwm_auto_temp; int force_pwm_max; int alarm; int* temp_min; int* temp_max; int* pwm_max; int* pwm_min; int* pwm_tmin; int /*<<< orphan*/  lock; void** fan_max; void** fan_min; void* alarms_mask; void** fan; int /*<<< orphan*/  temperatures_probed; struct i2c_client* client; } ;

/* Variables and functions */
 int ADT7470_FAN_COUNT ; 
 int ADT7470_FSPD_MASK ; 
 int ADT7470_OOL_ALARM ; 
 int ADT7470_PWM1_AUTO_MASK ; 
 int ADT7470_PWM2_AUTO_MASK ; 
 int ADT7470_PWM_COUNT ; 
 int ADT7470_REG_ALARM1 ; 
 int /*<<< orphan*/  ADT7470_REG_ALARM1_MASK ; 
 int ADT7470_REG_ALARM2 ; 
 int ADT7470_REG_CFG ; 
 int /*<<< orphan*/  ADT7470_REG_FAN (int) ; 
 int /*<<< orphan*/  ADT7470_REG_FAN_MAX (int) ; 
 int /*<<< orphan*/  ADT7470_REG_FAN_MIN (int) ; 
 int ADT7470_REG_PWM (int) ; 
 int ADT7470_REG_PWM_AUTO_TEMP (int) ; 
 int ADT7470_REG_PWM_CFG (int) ; 
 int ADT7470_REG_PWM_MAX (int) ; 
 int ADT7470_REG_PWM_MIN (int) ; 
 int ADT7470_REG_PWM_TMIN (int) ; 
 int ADT7470_TEMP_COUNT ; 
 int ADT7470_TEMP_MAX_REG (int) ; 
 int ADT7470_TEMP_MIN_REG (int) ; 
 int ADT7470_TEMP_REG (int) ; 
 int ALARM2 (int) ; 
 scalar_t__ LIMIT_REFRESH_INTERVAL ; 
 scalar_t__ SENSOR_REFRESH_INTERVAL ; 
 int /*<<< orphan*/  adt7470_read_temperatures (struct i2c_client*,struct adt7470_data*) ; 
 void* adt7470_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct adt7470_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 

__attribute__((used)) static struct adt7470_data *adt7470_update_device(struct device *dev)
{
	struct adt7470_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long local_jiffies = jiffies;
	u8 cfg;
	int i;
	int need_sensors = 1;
	int need_limits = 1;

	/*
	 * Figure out if we need to update the shadow registers.
	 * Lockless means that we may occasionally report out of
	 * date data.
	 */
	if (time_before(local_jiffies, data->sensors_last_updated +
			SENSOR_REFRESH_INTERVAL) &&
	    data->sensors_valid)
		need_sensors = 0;

	if (time_before(local_jiffies, data->limits_last_updated +
			LIMIT_REFRESH_INTERVAL) &&
	    data->limits_valid)
		need_limits = 0;

	if (!need_sensors && !need_limits)
		return data;

	mutex_lock(&data->lock);
	if (!need_sensors)
		goto no_sensor_update;

	if (!data->temperatures_probed)
		adt7470_read_temperatures(client, data);
	else
		for (i = 0; i < ADT7470_TEMP_COUNT; i++)
			data->temp[i] = i2c_smbus_read_byte_data(client,
						ADT7470_TEMP_REG(i));

	for (i = 0; i < ADT7470_FAN_COUNT; i++)
		data->fan[i] = adt7470_read_word_data(client,
						ADT7470_REG_FAN(i));

	for (i = 0; i < ADT7470_PWM_COUNT; i++) {
		int reg;
		int reg_mask;

		data->pwm[i] = i2c_smbus_read_byte_data(client,
						ADT7470_REG_PWM(i));

		if (i % 2)
			reg_mask = ADT7470_PWM2_AUTO_MASK;
		else
			reg_mask = ADT7470_PWM1_AUTO_MASK;

		reg = ADT7470_REG_PWM_CFG(i);
		if (i2c_smbus_read_byte_data(client, reg) & reg_mask)
			data->pwm_automatic[i] = 1;
		else
			data->pwm_automatic[i] = 0;

		reg = ADT7470_REG_PWM_AUTO_TEMP(i);
		cfg = i2c_smbus_read_byte_data(client, reg);
		if (!(i % 2))
			data->pwm_auto_temp[i] = cfg >> 4;
		else
			data->pwm_auto_temp[i] = cfg & 0xF;
	}

	if (i2c_smbus_read_byte_data(client, ADT7470_REG_CFG) &
	    ADT7470_FSPD_MASK)
		data->force_pwm_max = 1;
	else
		data->force_pwm_max = 0;

	data->alarm = i2c_smbus_read_byte_data(client, ADT7470_REG_ALARM1);
	if (data->alarm & ADT7470_OOL_ALARM)
		data->alarm |= ALARM2(i2c_smbus_read_byte_data(client,
							ADT7470_REG_ALARM2));
	data->alarms_mask = adt7470_read_word_data(client,
						   ADT7470_REG_ALARM1_MASK);

	data->sensors_last_updated = local_jiffies;
	data->sensors_valid = 1;

no_sensor_update:
	if (!need_limits)
		goto out;

	for (i = 0; i < ADT7470_TEMP_COUNT; i++) {
		data->temp_min[i] = i2c_smbus_read_byte_data(client,
						ADT7470_TEMP_MIN_REG(i));
		data->temp_max[i] = i2c_smbus_read_byte_data(client,
						ADT7470_TEMP_MAX_REG(i));
	}

	for (i = 0; i < ADT7470_FAN_COUNT; i++) {
		data->fan_min[i] = adt7470_read_word_data(client,
						ADT7470_REG_FAN_MIN(i));
		data->fan_max[i] = adt7470_read_word_data(client,
						ADT7470_REG_FAN_MAX(i));
	}

	for (i = 0; i < ADT7470_PWM_COUNT; i++) {
		data->pwm_max[i] = i2c_smbus_read_byte_data(client,
						ADT7470_REG_PWM_MAX(i));
		data->pwm_min[i] = i2c_smbus_read_byte_data(client,
						ADT7470_REG_PWM_MIN(i));
		data->pwm_tmin[i] = i2c_smbus_read_byte_data(client,
						ADT7470_REG_PWM_TMIN(i));
	}

	data->limits_last_updated = local_jiffies;
	data->limits_valid = 1;

out:
	mutex_unlock(&data->lock);
	return data;
}