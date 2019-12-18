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
typedef  int u16 ;
struct w83627ehf_data {int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83627EHF_REG_CASEOPEN_CLR ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
clear_caseopen(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct w83627ehf_data *data = dev_get_drvdata(dev);
	unsigned long val;
	u16 reg, mask;

	if (kstrtoul(buf, 10, &val) || val != 0)
		return -EINVAL;

	mask = to_sensor_dev_attr_2(attr)->nr;

	mutex_lock(&data->update_lock);
	reg = w83627ehf_read_value(data, W83627EHF_REG_CASEOPEN_CLR);
	w83627ehf_write_value(data, W83627EHF_REG_CASEOPEN_CLR, reg | mask);
	w83627ehf_write_value(data, W83627EHF_REG_CASEOPEN_CLR, reg & ~mask);
	data->valid = 0;	/* Force cache refresh */
	mutex_unlock(&data->update_lock);

	return count;
}