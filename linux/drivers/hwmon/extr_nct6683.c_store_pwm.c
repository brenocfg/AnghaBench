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
struct sensor_device_attribute_2 {int index; } ;
struct nct6683_data {int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long NCT6683_FAN_CFG_DONE ; 
 unsigned long NCT6683_FAN_CFG_REQ ; 
 int /*<<< orphan*/  NCT6683_REG_FAN_CFG_CTRL ; 
 int /*<<< orphan*/  NCT6683_REG_PWM_WRITE (int) ; 
 struct nct6683_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nct6683_write (struct nct6683_data*,int /*<<< orphan*/ ,unsigned long) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static ssize_t
store_pwm(struct device *dev, struct device_attribute *attr, const char *buf,
	  size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct nct6683_data *data = dev_get_drvdata(dev);
	int index = sattr->index;
	unsigned long val;

	if (kstrtoul(buf, 10, &val) || val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	nct6683_write(data, NCT6683_REG_FAN_CFG_CTRL, NCT6683_FAN_CFG_REQ);
	usleep_range(1000, 2000);
	nct6683_write(data, NCT6683_REG_PWM_WRITE(index), val);
	nct6683_write(data, NCT6683_REG_FAN_CFG_CTRL, NCT6683_FAN_CFG_DONE);
	mutex_unlock(&data->update_lock);

	return count;
}