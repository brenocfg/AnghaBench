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
struct TYPE_2__ {int (* hpf_enabled ) (struct dasd_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int dasd_nofcx ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct dasd_device*) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t dasd_hpf_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct dasd_device *device;
	int hpf;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return -ENODEV;
	if (!device->discipline || !device->discipline->hpf_enabled) {
		dasd_put_device(device);
		return snprintf(buf, PAGE_SIZE, "%d\n", dasd_nofcx);
	}
	hpf = device->discipline->hpf_enabled(device);
	dasd_put_device(device);
	return snprintf(buf, PAGE_SIZE, "%d\n", hpf);
}