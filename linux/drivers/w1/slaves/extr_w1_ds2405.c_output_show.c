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
struct w1_slave {struct w1_master* master; } ;
struct w1_master {int /*<<< orphan*/  bus_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct w1_slave* dev_to_w1_slave (struct device*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_ds2405_read_pio (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_reset_bus (struct w1_master*) ; 

__attribute__((used)) static ssize_t output_show(struct device *device,
			   struct device_attribute *attr, char *buf)
{
	struct w1_slave *sl = dev_to_w1_slave(device);
	struct w1_master *dev = sl->master;

	int ret;
	ssize_t f_retval;

	ret = mutex_lock_interruptible(&dev->bus_mutex);
	if (ret)
		return ret;

	ret = w1_ds2405_read_pio(sl);
	if (ret < 0) {
		f_retval = ret;
		goto out_unlock;
	}

	*buf = ret ? '1' : '0';
	f_retval = 1;

out_unlock:
	w1_reset_bus(dev);
	mutex_unlock(&dev->bus_mutex);

	return f_retval;
}