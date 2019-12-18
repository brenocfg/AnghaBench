#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fts_data {int valid; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  long ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  FTS_REG_FAN_CONTROL (int) ; 
 struct fts_data* dev_get_drvdata (struct device*) ; 
 long fts_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long fts_update_device (struct fts_data*) ; 
 long fts_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ kstrtoul (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
fan_alarm_store(struct device *dev, struct device_attribute *devattr,
		const char *buf, size_t count)
{
	struct fts_data *data = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr(devattr)->index;
	long ret;

	ret = fts_update_device(data);
	if (ret < 0)
		return ret;

	if (kstrtoul(buf, 10, &ret) || ret != 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	ret = fts_read_byte(data->client, FTS_REG_FAN_CONTROL(index));
	if (ret < 0)
		goto error;

	ret = fts_write_byte(data->client, FTS_REG_FAN_CONTROL(index),
			     ret | 0x1);
	if (ret < 0)
		goto error;

	data->valid = false;
	ret = count;
error:
	mutex_unlock(&data->update_lock);
	return ret;
}