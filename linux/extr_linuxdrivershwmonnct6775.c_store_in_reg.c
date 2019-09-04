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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct nct6775_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ ** in; int /*<<< orphan*/ ** REG_IN_MINMAX; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  in_to_reg (unsigned long,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_in_reg(struct device *dev, struct device_attribute *attr, const char *buf,
	     size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int index = sattr->index;
	int nr = sattr->nr;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;
	mutex_lock(&data->update_lock);
	data->in[nr][index] = in_to_reg(val, nr);
	nct6775_write_value(data, data->REG_IN_MINMAX[index - 1][nr],
			    data->in[nr][index]);
	mutex_unlock(&data->update_lock);
	return count;
}