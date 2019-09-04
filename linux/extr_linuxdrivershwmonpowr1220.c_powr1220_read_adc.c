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
struct powr1220_data {int* adc_valid; int* adc_maxes; int* adc_values; int /*<<< orphan*/  update_lock; scalar_t__* adc_last_updated; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ADC_MAX_LOW_MEASUREMENT_MV ; 
 int /*<<< orphan*/  ADC_MUX ; 
 int ADC_STEP_MV ; 
 int /*<<< orphan*/  ADC_VALUE_HIGH ; 
 int /*<<< orphan*/  ADC_VALUE_LOW ; 
 scalar_t__ HZ ; 
 struct powr1220_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int powr1220_read_adc(struct device *dev, int ch_num)
{
	struct powr1220_data *data = dev_get_drvdata(dev);
	int reading;
	int result;
	int adc_range = 0;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->adc_last_updated[ch_num] + HZ) ||
			!data->adc_valid[ch_num]) {
		/*
		 * figure out if we need to use the attenuator for
		 * high inputs or inputs that we don't yet have a measurement
		 * for. We dynamically set the attenuator depending on the
		 * max reading.
		 */
		if (data->adc_maxes[ch_num] > ADC_MAX_LOW_MEASUREMENT_MV ||
				data->adc_maxes[ch_num] == 0)
			adc_range = 1 << 4;

		/* set the attenuator and mux */
		result = i2c_smbus_write_byte_data(data->client, ADC_MUX,
				adc_range | ch_num);
		if (result)
			goto exit;

		/*
		 * wait at least Tconvert time (200 us) for the
		 * conversion to complete
		 */
		udelay(200);

		/* get the ADC reading */
		result = i2c_smbus_read_byte_data(data->client, ADC_VALUE_LOW);
		if (result < 0)
			goto exit;

		reading = result >> 4;

		/* get the upper half of the reading */
		result = i2c_smbus_read_byte_data(data->client, ADC_VALUE_HIGH);
		if (result < 0)
			goto exit;

		reading |= result << 4;

		/* now convert the reading to a voltage */
		reading *= ADC_STEP_MV;
		data->adc_values[ch_num] = reading;
		data->adc_valid[ch_num] = true;
		data->adc_last_updated[ch_num] = jiffies;
		result = reading;

		if (reading > data->adc_maxes[ch_num])
			data->adc_maxes[ch_num] = reading;
	} else {
		result = data->adc_values[ch_num];
	}

exit:
	mutex_unlock(&data->update_lock);

	return result;
}