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
struct sensor_device_attribute_2 {size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int config5; int** temp; int* range; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 size_t AUTOMIN ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  REG_CONFIG5 ; 
 int /*<<< orphan*/  TEMP_TMIN_REG (size_t) ; 
 int /*<<< orphan*/  TEMP_TRANGE_REG (size_t) ; 
 int adt7475_read (int /*<<< orphan*/ ) ; 
 scalar_t__* autorange_table ; 
 long clamp_val (long,scalar_t__,scalar_t__) ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 long find_closest (long,scalar_t__*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reg2temp (struct adt7475_data*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t point2_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct adt7475_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int temp;
	long val;

	if (kstrtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);

	/* Get a fresh copy of the needed registers */
	data->config5 = adt7475_read(REG_CONFIG5);
	data->temp[AUTOMIN][sattr->index] =
		adt7475_read(TEMP_TMIN_REG(sattr->index)) << 2;
	data->range[sattr->index] =
		adt7475_read(TEMP_TRANGE_REG(sattr->index));

	/*
	 * The user will write an absolute value, so subtract the start point
	 * to figure the range
	 */
	temp = reg2temp(data, data->temp[AUTOMIN][sattr->index]);
	val = clamp_val(val, temp + autorange_table[0],
		temp + autorange_table[ARRAY_SIZE(autorange_table) - 1]);
	val -= temp;

	/* Find the nearest table entry to what the user wrote */
	val = find_closest(val, autorange_table, ARRAY_SIZE(autorange_table));

	data->range[sattr->index] &= ~0xF0;
	data->range[sattr->index] |= val << 4;

	i2c_smbus_write_byte_data(client, TEMP_TRANGE_REG(sattr->index),
				  data->range[sattr->index]);

	mutex_unlock(&data->lock);
	return count;
}