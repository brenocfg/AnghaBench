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
struct nct6775_data {int have_temp; int* temp_src; int* pwm_temp_sel; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * REG_TEMP_SEL; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BIT (unsigned long) ; 
 int EINVAL ; 
 unsigned long NUM_TEMP ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 struct nct6775_data* nct6775_update_device (struct device*) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_pwm_temp_sel(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct nct6775_data *data = nct6775_update_device(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	int nr = sattr->index;
	unsigned long val;
	int err, reg, src;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;
	if (val == 0 || val > NUM_TEMP)
		return -EINVAL;
	if (!(data->have_temp & BIT(val - 1)) || !data->temp_src[val - 1])
		return -EINVAL;

	mutex_lock(&data->update_lock);
	src = data->temp_src[val - 1];
	data->pwm_temp_sel[nr] = src;
	reg = nct6775_read_value(data, data->REG_TEMP_SEL[nr]);
	reg &= 0xe0;
	reg |= src;
	nct6775_write_value(data, data->REG_TEMP_SEL[nr], reg);
	mutex_unlock(&data->update_lock);

	return count;
}