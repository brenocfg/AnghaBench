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
struct ad7418_data {int valid; int* temp; int adc_max; int* in; int /*<<< orphan*/  lock; scalar_t__ last_updated; struct i2c_client* client; } ;
typedef  int s32 ;

/* Variables and functions */
 int AD7418_CH_TEMP ; 
 int /*<<< orphan*/  AD7418_REG_ADC ; 
 int AD7418_REG_ADC_CH (int) ; 
 int /*<<< orphan*/  AD7418_REG_CONF ; 
 int /*<<< orphan*/ * AD7418_REG_TEMP ; 
 int HZ ; 
 struct ad7418_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ad7418_update_device(struct device *dev)
{
	struct ad7418_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	s32 val;

	mutex_lock(&data->lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
		|| !data->valid) {
		u8 cfg;
		int i, ch;

		/* read config register and clear channel bits */
		val = i2c_smbus_read_byte_data(client, AD7418_REG_CONF);
		if (val < 0)
			goto abort;

		cfg = val;
		cfg &= 0x1F;

		val = i2c_smbus_write_byte_data(client, AD7418_REG_CONF,
						cfg | AD7418_CH_TEMP);
		if (val < 0)
			goto abort;

		udelay(30);

		for (i = 0; i < 3; i++) {
			val = i2c_smbus_read_word_swapped(client,
							  AD7418_REG_TEMP[i]);
			if (val < 0)
				goto abort;

			data->temp[i] = val;
		}

		for (i = 0, ch = 4; i < data->adc_max; i++, ch--) {
			val = i2c_smbus_write_byte_data(client, AD7418_REG_CONF,
					cfg | AD7418_REG_ADC_CH(ch));
			if (val < 0)
				goto abort;

			udelay(15);
			val = i2c_smbus_read_word_swapped(client,
							  AD7418_REG_ADC);
			if (val < 0)
				goto abort;

			data->in[data->adc_max - 1 - i] = val;
		}

		/* restore old configuration value */
		val = i2c_smbus_write_word_swapped(client, AD7418_REG_CONF,
						   cfg);
		if (val < 0)
			goto abort;

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->lock);
	return 0;

abort:
	data->valid = 0;
	mutex_unlock(&data->lock);
	return val;
}