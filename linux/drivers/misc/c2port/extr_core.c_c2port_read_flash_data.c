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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct c2port_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flash_access; int /*<<< orphan*/  access; } ;
struct bin_attribute {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ __c2port_read_flash_data (struct c2port_device*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct c2port_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t c2port_read_flash_data(struct file *filp, struct kobject *kobj,
				struct bin_attribute *attr,
				char *buffer, loff_t offset, size_t count)
{
	struct c2port_device *c2dev = dev_get_drvdata(kobj_to_dev(kobj));
	ssize_t ret;

	/* Check the device and flash access status */
	if (!c2dev->access || !c2dev->flash_access)
		return -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_read_flash_data(c2dev, buffer, offset, count);
	mutex_unlock(&c2dev->mutex);

	if (ret < 0)
		dev_err(c2dev->dev, "cannot read %s flash\n", c2dev->name);

	return ret;
}