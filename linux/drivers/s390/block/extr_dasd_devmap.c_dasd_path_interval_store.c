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
struct dasd_device {unsigned long path_interval; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long DASD_INTERVAL_MAX ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_path_interval_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct dasd_device *device;
	unsigned long flags;
	unsigned long val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return -ENODEV;

	if ((kstrtoul(buf, 10, &val) != 0) ||
	    (val > DASD_INTERVAL_MAX) || val == 0) {
		dasd_put_device(device);
		return -EINVAL;
	}
	spin_lock_irqsave(get_ccwdev_lock(to_ccwdev(dev)), flags);
	if (val)
		device->path_interval = val;
	spin_unlock_irqrestore(get_ccwdev_lock(to_ccwdev(dev)), flags);
	dasd_put_device(device);
	return count;
}