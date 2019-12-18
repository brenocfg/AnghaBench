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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7470_data {int /*<<< orphan*/  lock; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned char ADT7470_CFG_LF ; 
 unsigned char ADT7470_FREQ_MASK ; 
 int ADT7470_FREQ_SHIFT ; 
 int /*<<< orphan*/  ADT7470_REG_CFG ; 
 int /*<<< orphan*/  ADT7470_REG_CFG_2 ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  adt7470_freq_map ; 
 struct adt7470_data* dev_get_drvdata (struct device*) ; 
 int find_closest (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm1_freq_store(struct device *dev,
			       struct device_attribute *devattr,
			       const char *buf, size_t count)
{
	struct adt7470_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long freq;
	int index;
	int low_freq = ADT7470_CFG_LF;
	unsigned char val;

	if (kstrtol(buf, 10, &freq))
		return -EINVAL;

	/* Round the user value given to the closest available frequency */
	index = find_closest(freq, adt7470_freq_map,
			     ARRAY_SIZE(adt7470_freq_map));

	if (index >= 8) {
		index -= 8;
		low_freq = 0;
	}

	mutex_lock(&data->lock);
	/* Configuration Register 1 */
	val = i2c_smbus_read_byte_data(client, ADT7470_REG_CFG);
	i2c_smbus_write_byte_data(client, ADT7470_REG_CFG,
				  (val & ~ADT7470_CFG_LF) | low_freq);
	/* Configuration Register 2 */
	val = i2c_smbus_read_byte_data(client, ADT7470_REG_CFG_2);
	i2c_smbus_write_byte_data(client, ADT7470_REG_CFG_2,
		(val & ~ADT7470_FREQ_MASK) | (index << ADT7470_FREQ_SHIFT));
	mutex_unlock(&data->lock);

	return count;
}