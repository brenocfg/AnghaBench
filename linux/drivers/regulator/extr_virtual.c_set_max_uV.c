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
struct virtual_consumer_data {long max_uV; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct virtual_consumer_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_voltage_constraints (struct device*,struct virtual_consumer_data*) ; 

__attribute__((used)) static ssize_t set_max_uV(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct virtual_consumer_data *data = dev_get_drvdata(dev);
	long val;

	if (kstrtol(buf, 10, &val) != 0)
		return count;

	mutex_lock(&data->lock);

	data->max_uV = val;
	update_voltage_constraints(dev, data);

	mutex_unlock(&data->lock);

	return count;
}