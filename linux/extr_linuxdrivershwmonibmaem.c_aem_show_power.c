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
typedef  int u64 ;
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aem_data {int* energy; int /*<<< orphan*/  lock; int /*<<< orphan*/ * power_period; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int UJ_PER_MJ ; 
 struct aem_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ div64_u64 (int,int) ; 
 int ktime_get_ns () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  update_aem_energy_one (struct aem_data*,size_t) ; 

__attribute__((used)) static ssize_t aem_show_power(struct device *dev,
			      struct device_attribute *devattr,
			      char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct aem_data *data = dev_get_drvdata(dev);
	u64 before, after, delta, time;
	signed long leftover;

	mutex_lock(&data->lock);
	update_aem_energy_one(data, attr->index);
	time = ktime_get_ns();
	before = data->energy[attr->index];

	leftover = schedule_timeout_interruptible(
			msecs_to_jiffies(data->power_period[attr->index])
		   );
	if (leftover) {
		mutex_unlock(&data->lock);
		return 0;
	}

	update_aem_energy_one(data, attr->index);
	time = ktime_get_ns() - time;
	after = data->energy[attr->index];
	mutex_unlock(&data->lock);

	delta = (after - before) * UJ_PER_MJ;

	return sprintf(buf, "%llu\n",
		(unsigned long long)div64_u64(delta * NSEC_PER_SEC, time));
}