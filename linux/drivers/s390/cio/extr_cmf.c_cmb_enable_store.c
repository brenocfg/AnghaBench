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
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int disable_cmf (struct ccw_device*) ; 
 int enable_cmf (struct ccw_device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t cmb_enable_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t c)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	switch (val) {
	case 0:
		ret = disable_cmf(cdev);
		break;
	case 1:
		ret = enable_cmf(cdev);
		break;
	default:
		ret = -EINVAL;
	}

	return ret ? ret : c;
}