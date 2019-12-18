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
struct sensor_device_attribute {int index; } ;
struct lm73_data {int ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LM73_REG_CTRL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm73_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t maxmin_alarm_show(struct device *dev,
				 struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm73_data *data = dev_get_drvdata(dev);
	s32 ctrl;

	mutex_lock(&data->lock);
	ctrl = i2c_smbus_read_byte_data(data->client, LM73_REG_CTRL);
	if (ctrl < 0)
		goto abort;
	data->ctrl = ctrl;
	mutex_unlock(&data->lock);

	return scnprintf(buf, PAGE_SIZE, "%d\n", (ctrl >> attr->index) & 1);

abort:
	mutex_unlock(&data->lock);
	return ctrl;
}