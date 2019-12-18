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
struct c2port_device {int /*<<< orphan*/  name; int /*<<< orphan*/  mutex; int /*<<< orphan*/  access; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ __c2port_show_dev_id (struct c2port_device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct c2port_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t c2port_show_dev_id(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct c2port_device *c2dev = dev_get_drvdata(dev);
	ssize_t ret;

	/* Check the device access status */
	if (!c2dev->access)
		return -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_show_dev_id(c2dev, buf);
	mutex_unlock(&c2dev->mutex);

	if (ret < 0)
		dev_err(dev, "cannot read from %s\n", c2dev->name);

	return ret;
}