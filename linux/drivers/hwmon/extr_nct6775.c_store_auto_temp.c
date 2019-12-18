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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct nct6775_data {int auto_pwm_num; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ ** auto_temp; int /*<<< orphan*/ * REG_CRITICAL_TEMP; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NCT6775_AUTO_TEMP (struct nct6775_data*,int,int) ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_auto_temp(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int nr = sattr->nr;
	int point = sattr->index;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;
	if (val > 255000)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->auto_temp[nr][point] = DIV_ROUND_CLOSEST(val, 1000);
	if (point < data->auto_pwm_num) {
		nct6775_write_value(data,
				    NCT6775_AUTO_TEMP(data, nr, point),
				    data->auto_temp[nr][point]);
	} else {
		nct6775_write_value(data, data->REG_CRITICAL_TEMP[nr],
				    data->auto_temp[nr][point]);
	}
	mutex_unlock(&data->update_lock);
	return count;
}