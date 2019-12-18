#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm85_data {scalar_t__ type; int cfg5; int* pwm_freq; int /*<<< orphan*/  update_lock; TYPE_1__* zone; int /*<<< orphan*/  freq_map_size; int /*<<< orphan*/  freq_map; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int range; } ;

/* Variables and functions */
 int ADT7468_HFPWM ; 
 int /*<<< orphan*/  ADT7468_REG_CFG5 ; 
 int FREQ_TO_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  LM85_REG_AFAN_RANGE (int) ; 
 scalar_t__ adt7468 ; 
 struct lm85_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  lm85_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_freq_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	/*
	 * The ADT7468 has a special high-frequency PWM output mode,
	 * where all PWM outputs are driven by a 22.5 kHz clock.
	 * This might confuse the user, but there's not much we can do.
	 */
	if (data->type == adt7468 && val >= 11300) {	/* High freq. mode */
		data->cfg5 &= ~ADT7468_HFPWM;
		lm85_write_value(client, ADT7468_REG_CFG5, data->cfg5);
	} else {					/* Low freq. mode */
		data->pwm_freq[nr] = FREQ_TO_REG(data->freq_map,
						 data->freq_map_size, val);
		lm85_write_value(client, LM85_REG_AFAN_RANGE(nr),
				 (data->zone[nr].range << 4)
				 | data->pwm_freq[nr]);
		if (data->type == adt7468) {
			data->cfg5 |= ADT7468_HFPWM;
			lm85_write_value(client, ADT7468_REG_CFG5, data->cfg5);
		}
	}
	mutex_unlock(&data->update_lock);
	return count;
}