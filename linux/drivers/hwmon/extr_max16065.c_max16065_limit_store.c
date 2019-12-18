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
struct sensor_device_attribute_2 {size_t index; size_t nr; } ;
struct max16065_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; int /*<<< orphan*/ * range; int /*<<< orphan*/ ** limit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_TO_MV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX16065_LIMIT (size_t,size_t) ; 
 int MV_TO_LIMIT (unsigned long,int /*<<< orphan*/ ) ; 
 struct max16065_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t max16065_limit_store(struct device *dev,
				    struct device_attribute *da,
				    const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(da);
	struct max16065_data *data = dev_get_drvdata(dev);
	unsigned long val;
	int err;
	int limit;

	err = kstrtoul(buf, 10, &val);
	if (unlikely(err < 0))
		return err;

	limit = MV_TO_LIMIT(val, data->range[attr2->index]);

	mutex_lock(&data->update_lock);
	data->limit[attr2->nr][attr2->index]
	  = LIMIT_TO_MV(limit, data->range[attr2->index]);
	i2c_smbus_write_byte_data(data->client,
				  MAX16065_LIMIT(attr2->nr, attr2->index),
				  limit);
	mutex_unlock(&data->update_lock);

	return count;
}