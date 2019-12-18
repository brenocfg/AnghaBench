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
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* host_access_count ) (struct dasd_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct dasd_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_access_show(struct device *dev, struct device_attribute *attr,
		 char *buf)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct dasd_device *device;
	int count;

	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device))
		return PTR_ERR(device);

	if (!device->discipline)
		count = -ENODEV;
	else if (!device->discipline->host_access_count)
		count = -EOPNOTSUPP;
	else
		count = device->discipline->host_access_count(device);

	dasd_put_device(device);
	if (count < 0)
		return count;

	return sprintf(buf, "%d\n", count);
}