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
struct dasd_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 size_t PTR_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_disable (struct dasd_device*) ; 
 int dasd_eer_enable (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_eer_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct dasd_device *device;
	unsigned int val;
	int rc = 0;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return PTR_ERR(device);

	if (kstrtouint(buf, 0, &val) || val > 1)
		return -EINVAL;

	if (val)
		rc = dasd_eer_enable(device);
	else
		dasd_eer_disable(device);

	dasd_put_device(device);

	return rc ? : count;
}