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
struct lm63_data {unsigned long last_updated; int valid; int config; int* fan; int pwm1_freq; int* pwm1; int* temp8; int* temp11; scalar_t__ kind; int temp11u; int temp2_crit_hyst; int alarms; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM63_REG_ALERT_STATUS ; 
 int /*<<< orphan*/  LM63_REG_LOCAL_HIGH ; 
 int /*<<< orphan*/  LM63_REG_LOCAL_TEMP ; 
 int /*<<< orphan*/  LM63_REG_PWM_FREQ ; 
 int /*<<< orphan*/  LM63_REG_PWM_VALUE ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_HIGH_LSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_HIGH_MSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_LOW_LSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_LOW_MSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_OFFSET_LSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_OFFSET_MSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TCRIT ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TCRIT_HYST ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TEMP_LSB ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TEMP_MSB ; 
 int /*<<< orphan*/  LM63_REG_TACH_COUNT_LSB ; 
 int /*<<< orphan*/  LM63_REG_TACH_COUNT_MSB ; 
 int /*<<< orphan*/  LM63_REG_TACH_LIMIT_LSB ; 
 int /*<<< orphan*/  LM63_REG_TACH_LIMIT_MSB ; 
 int /*<<< orphan*/  LM96163_REG_REMOTE_TEMP_U_LSB ; 
 int /*<<< orphan*/  LM96163_REG_REMOTE_TEMP_U_MSB ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lm63_update_lut (struct lm63_data*) ; 
 scalar_t__ lm96163 ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static struct lm63_data *lm63_update_device(struct device *dev)
{
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long next_update;

	mutex_lock(&data->update_lock);

	next_update = data->last_updated +
		      msecs_to_jiffies(data->update_interval);
	if (time_after(jiffies, next_update) || !data->valid) {
		if (data->config & 0x04) { /* tachometer enabled  */
			/* order matters for fan1_input */
			data->fan[0] = i2c_smbus_read_byte_data(client,
				       LM63_REG_TACH_COUNT_LSB) & 0xFC;
			data->fan[0] |= i2c_smbus_read_byte_data(client,
					LM63_REG_TACH_COUNT_MSB) << 8;
			data->fan[1] = (i2c_smbus_read_byte_data(client,
					LM63_REG_TACH_LIMIT_LSB) & 0xFC)
				     | (i2c_smbus_read_byte_data(client,
					LM63_REG_TACH_LIMIT_MSB) << 8);
		}

		data->pwm1_freq = i2c_smbus_read_byte_data(client,
				  LM63_REG_PWM_FREQ);
		if (data->pwm1_freq == 0)
			data->pwm1_freq = 1;
		data->pwm1[0] = i2c_smbus_read_byte_data(client,
				LM63_REG_PWM_VALUE);

		data->temp8[0] = i2c_smbus_read_byte_data(client,
				 LM63_REG_LOCAL_TEMP);
		data->temp8[1] = i2c_smbus_read_byte_data(client,
				 LM63_REG_LOCAL_HIGH);

		/* order matters for temp2_input */
		data->temp11[0] = i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_TEMP_MSB) << 8;
		data->temp11[0] |= i2c_smbus_read_byte_data(client,
				   LM63_REG_REMOTE_TEMP_LSB);
		data->temp11[1] = (i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_LOW_MSB) << 8)
				| i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_LOW_LSB);
		data->temp11[2] = (i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_HIGH_MSB) << 8)
				| i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_HIGH_LSB);
		data->temp11[3] = (i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_OFFSET_MSB) << 8)
				| i2c_smbus_read_byte_data(client,
				  LM63_REG_REMOTE_OFFSET_LSB);

		if (data->kind == lm96163)
			data->temp11u = (i2c_smbus_read_byte_data(client,
					LM96163_REG_REMOTE_TEMP_U_MSB) << 8)
				      | i2c_smbus_read_byte_data(client,
					LM96163_REG_REMOTE_TEMP_U_LSB);

		data->temp8[2] = i2c_smbus_read_byte_data(client,
				 LM63_REG_REMOTE_TCRIT);
		data->temp2_crit_hyst = i2c_smbus_read_byte_data(client,
					LM63_REG_REMOTE_TCRIT_HYST);

		data->alarms = i2c_smbus_read_byte_data(client,
			       LM63_REG_ALERT_STATUS) & 0x7F;

		data->last_updated = jiffies;
		data->valid = 1;
	}

	lm63_update_lut(data);

	mutex_unlock(&data->update_lock);

	return data;
}