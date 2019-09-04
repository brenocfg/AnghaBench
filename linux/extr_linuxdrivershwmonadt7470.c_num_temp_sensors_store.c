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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7470_data {long num_temp_sensors; int /*<<< orphan*/  lock; scalar_t__ temperatures_probed; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 long clamp_val (long,int,int) ; 
 struct adt7470_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t num_temp_sensors_store(struct device *dev,
				      struct device_attribute *devattr,
				      const char *buf, size_t count)
{
	struct adt7470_data *data = dev_get_drvdata(dev);
	long temp;

	if (kstrtol(buf, 10, &temp))
		return -EINVAL;

	temp = clamp_val(temp, -1, 10);

	mutex_lock(&data->lock);
	data->num_temp_sensors = temp;
	if (temp < 0)
		data->temperatures_probed = 0;
	mutex_unlock(&data->lock);

	return count;
}