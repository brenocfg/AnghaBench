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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct adc128_data {int valid; size_t mode; int** in; int* temp; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC128_REG_ALARM ; 
 int /*<<< orphan*/  ADC128_REG_IN (int) ; 
 int /*<<< orphan*/  ADC128_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  ADC128_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  ADC128_REG_TEMP ; 
 int /*<<< orphan*/  ADC128_REG_TEMP_HYST ; 
 int /*<<< orphan*/  ADC128_REG_TEMP_MAX ; 
 struct adc128_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 struct adc128_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* num_inputs ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct adc128_data *adc128_update_device(struct device *dev)
{
	struct adc128_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct adc128_data *ret = data;
	int i, rv;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		for (i = 0; i < num_inputs[data->mode]; i++) {
			rv = i2c_smbus_read_word_swapped(client,
							 ADC128_REG_IN(i));
			if (rv < 0)
				goto abort;
			data->in[0][i] = rv >> 4;

			rv = i2c_smbus_read_byte_data(client,
						      ADC128_REG_IN_MIN(i));
			if (rv < 0)
				goto abort;
			data->in[1][i] = rv << 4;

			rv = i2c_smbus_read_byte_data(client,
						      ADC128_REG_IN_MAX(i));
			if (rv < 0)
				goto abort;
			data->in[2][i] = rv << 4;
		}

		if (data->mode != 1) {
			rv = i2c_smbus_read_word_swapped(client,
							 ADC128_REG_TEMP);
			if (rv < 0)
				goto abort;
			data->temp[0] = rv >> 7;

			rv = i2c_smbus_read_byte_data(client,
						      ADC128_REG_TEMP_MAX);
			if (rv < 0)
				goto abort;
			data->temp[1] = rv << 1;

			rv = i2c_smbus_read_byte_data(client,
						      ADC128_REG_TEMP_HYST);
			if (rv < 0)
				goto abort;
			data->temp[2] = rv << 1;
		}

		rv = i2c_smbus_read_byte_data(client, ADC128_REG_ALARM);
		if (rv < 0)
			goto abort;
		data->alarms |= rv;

		data->last_updated = jiffies;
		data->valid = true;
	}
	goto done;

abort:
	ret = ERR_PTR(rv);
	data->valid = false;
done:
	mutex_unlock(&data->update_lock);
	return ret;
}