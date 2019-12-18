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
struct dasd_device {TYPE_1__* block; int /*<<< orphan*/  flags; } ;
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  open_count; int /*<<< orphan*/  gdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int dasd_set_feature (struct ccw_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_ro_store(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct dasd_device *device;
	unsigned long flags;
	unsigned int val;
	int rc;

	if (kstrtouint(buf, 0, &val) || val > 1)
		return -EINVAL;

	rc = dasd_set_feature(cdev, DASD_FEATURE_READONLY, val);
	if (rc)
		return rc;

	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device))
		return count;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	val = val || test_bit(DASD_FLAG_DEVICE_RO, &device->flags);

	if (!device->block || !device->block->gdp ||
	    test_bit(DASD_FLAG_OFFLINE, &device->flags)) {
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		goto out;
	}
	/* Increase open_count to avoid losing the block device */
	atomic_inc(&device->block->open_count);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	set_disk_ro(device->block->gdp, val);
	atomic_dec(&device->block->open_count);

out:
	dasd_put_device(device);

	return count;
}