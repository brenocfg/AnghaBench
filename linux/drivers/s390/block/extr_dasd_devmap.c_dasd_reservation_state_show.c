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
struct dasd_device {int /*<<< orphan*/  flags; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_IS_RESERVED ; 
 int /*<<< orphan*/  DASD_FLAG_LOCK_STOLEN ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t dasd_reservation_state_show(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct dasd_device *device;
	int rc = 0;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return snprintf(buf, PAGE_SIZE, "none\n");

	if (test_bit(DASD_FLAG_IS_RESERVED, &device->flags))
		rc = snprintf(buf, PAGE_SIZE, "reserved\n");
	else if (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags))
		rc = snprintf(buf, PAGE_SIZE, "lost\n");
	else
		rc = snprintf(buf, PAGE_SIZE, "none\n");
	dasd_put_device(device);
	return rc;
}