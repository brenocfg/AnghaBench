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
struct mei_device {int dev_state; int /*<<< orphan*/  device_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum mei_dev_state { ____Placeholder_mei_dev_state } mei_dev_state ;

/* Variables and functions */
 struct mei_device* dev_get_drvdata (struct device*) ; 
 char* mei_dev_state_str (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t dev_state_show(struct device *device,
			      struct device_attribute *attr, char *buf)
{
	struct mei_device *dev = dev_get_drvdata(device);
	enum mei_dev_state dev_state;

	mutex_lock(&dev->device_lock);
	dev_state = dev->dev_state;
	mutex_unlock(&dev->device_lock);

	return sprintf(buf, "%s", mei_dev_state_str(dev_state));
}