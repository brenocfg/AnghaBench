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
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2438_STATUS_IAD ; 
 int EFAULT ; 
 int EIO ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w1_ds2438_change_config_bit (struct w1_slave*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static ssize_t iad_write(struct file *filp, struct kobject *kobj,
			 struct bin_attribute *bin_attr, char *buf,
			 loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int ret;

	if (count != 1 || off != 0)
		return -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	if (w1_ds2438_change_config_bit(sl, DS2438_STATUS_IAD, *buf & 0x01) == 0)
		ret = 1;
	else
		ret = -EIO;

	mutex_unlock(&sl->master->bus_mutex);

	return ret;
}