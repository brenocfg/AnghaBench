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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute_2 {scalar_t__ index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * enh_acoustics; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  REG_ENHANCE_ACOUSTICS1 ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t stall_disable_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct adt7475_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	u8 mask = BIT(5 + sattr->index);

	if (kstrtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);

	data->enh_acoustics[0] &= ~mask;
	if (val)
		data->enh_acoustics[0] |= mask;

	i2c_smbus_write_byte_data(client, REG_ENHANCE_ACOUSTICS1,
				  data->enh_acoustics[0]);

	mutex_unlock(&data->lock);

	return count;
}