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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dasd_device {TYPE_1__* discipline; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_discipline_show(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct dasd_device *device;
	ssize_t len;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		goto out;
	else if (!device->discipline) {
		dasd_put_device(device);
		goto out;
	} else {
		len = snprintf(buf, PAGE_SIZE, "%s\n",
			       device->discipline->name);
		dasd_put_device(device);
		return len;
	}
out:
	len = snprintf(buf, PAGE_SIZE, "none\n");
	return len;
}