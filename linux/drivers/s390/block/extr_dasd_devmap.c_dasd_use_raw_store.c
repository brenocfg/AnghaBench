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
struct dasd_devmap {int features; int /*<<< orphan*/  device; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int DASD_FEATURE_USEDIAG ; 
 int DASD_FEATURE_USERAW ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 size_t PTR_ERR (struct dasd_devmap*) ; 
 struct dasd_devmap* dasd_devmap_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_use_raw_store(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t count)
{
	struct dasd_devmap *devmap;
	ssize_t rc;
	unsigned long val;

	devmap = dasd_devmap_from_cdev(to_ccwdev(dev));
	if (IS_ERR(devmap))
		return PTR_ERR(devmap);

	if ((kstrtoul(buf, 10, &val) != 0) || val > 1)
		return -EINVAL;

	spin_lock(&dasd_devmap_lock);
	/* Changing diag discipline flag is only allowed in offline state. */
	rc = count;
	if (!devmap->device && !(devmap->features & DASD_FEATURE_USEDIAG)) {
		if (val)
			devmap->features |= DASD_FEATURE_USERAW;
		else
			devmap->features &= ~DASD_FEATURE_USERAW;
	} else
		rc = -EPERM;
	spin_unlock(&dasd_devmap_lock);
	return rc;
}