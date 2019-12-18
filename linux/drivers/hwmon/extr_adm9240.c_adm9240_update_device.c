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
struct adm9240_data {int valid; int* in; int alarms; int temp; int* fan; int* fan_div; int* fan_min; int* in_min; int* in_max; int* temp_max; int vid; int aout; int /*<<< orphan*/  update_lock; void* last_updated_config; void* last_updated_measure; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM9240_REG_ANALOG_OUT ; 
 int /*<<< orphan*/  ADM9240_REG_FAN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_IN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_INT (int) ; 
 int /*<<< orphan*/  ADM9240_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  ADM9240_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_TEMP ; 
 int /*<<< orphan*/  ADM9240_REG_TEMP_CONF ; 
 int /*<<< orphan*/  ADM9240_REG_TEMP_MAX (int) ; 
 int /*<<< orphan*/  ADM9240_REG_VID4 ; 
 int /*<<< orphan*/  ADM9240_REG_VID_FAN_DIV ; 
 int HZ ; 
 int /*<<< orphan*/  adm9240_write_fan_div (struct i2c_client*,int,int) ; 
 struct adm9240_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (void*,void*) ; 

__attribute__((used)) static struct adm9240_data *adm9240_update_device(struct device *dev)
{
	struct adm9240_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i;

	mutex_lock(&data->update_lock);

	/* minimum measurement cycle: 1.75 seconds */
	if (time_after(jiffies, data->last_updated_measure + (HZ * 7 / 4))
			|| !data->valid) {

		for (i = 0; i < 6; i++) { /* read voltages */
			data->in[i] = i2c_smbus_read_byte_data(client,
					ADM9240_REG_IN(i));
		}
		data->alarms = i2c_smbus_read_byte_data(client,
					ADM9240_REG_INT(0)) |
					i2c_smbus_read_byte_data(client,
					ADM9240_REG_INT(1)) << 8;

		/*
		 * read temperature: assume temperature changes less than
		 * 0.5'C per two measurement cycles thus ignore possible
		 * but unlikely aliasing error on lsb reading. --Grant
		 */
		data->temp = (i2c_smbus_read_byte_data(client,
					ADM9240_REG_TEMP) << 8) |
					i2c_smbus_read_byte_data(client,
					ADM9240_REG_TEMP_CONF);

		for (i = 0; i < 2; i++) { /* read fans */
			data->fan[i] = i2c_smbus_read_byte_data(client,
					ADM9240_REG_FAN(i));

			/* adjust fan clock divider on overflow */
			if (data->valid && data->fan[i] == 255 &&
					data->fan_div[i] < 3) {

				adm9240_write_fan_div(client, i,
						++data->fan_div[i]);

				/* adjust fan_min if active, but not to 0 */
				if (data->fan_min[i] < 255 &&
						data->fan_min[i] >= 2)
					data->fan_min[i] /= 2;
			}
		}
		data->last_updated_measure = jiffies;
	}

	/* minimum config reading cycle: 300 seconds */
	if (time_after(jiffies, data->last_updated_config + (HZ * 300))
			|| !data->valid) {

		for (i = 0; i < 6; i++) {
			data->in_min[i] = i2c_smbus_read_byte_data(client,
					ADM9240_REG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_read_byte_data(client,
					ADM9240_REG_IN_MAX(i));
		}
		for (i = 0; i < 2; i++) {
			data->fan_min[i] = i2c_smbus_read_byte_data(client,
					ADM9240_REG_FAN_MIN(i));
		}
		data->temp_max[0] = i2c_smbus_read_byte_data(client,
				ADM9240_REG_TEMP_MAX(0));
		data->temp_max[1] = i2c_smbus_read_byte_data(client,
				ADM9240_REG_TEMP_MAX(1));

		/* read fan divs and 5-bit VID */
		i = i2c_smbus_read_byte_data(client, ADM9240_REG_VID_FAN_DIV);
		data->fan_div[0] = (i >> 4) & 3;
		data->fan_div[1] = (i >> 6) & 3;
		data->vid = i & 0x0f;
		data->vid |= (i2c_smbus_read_byte_data(client,
					ADM9240_REG_VID4) & 1) << 4;
		/* read analog out */
		data->aout = i2c_smbus_read_byte_data(client,
				ADM9240_REG_ANALOG_OUT);

		data->last_updated_config = jiffies;
		data->valid = 1;
	}
	mutex_unlock(&data->update_lock);
	return data;
}