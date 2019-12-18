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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ab8500_rtc_set_calibration (struct device*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t ab8500_sysfs_store_rtc_calibration(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	int retval;
	int calibration = 0;

	if (sscanf(buf, " %i ", &calibration) != 1) {
		dev_err(dev, "Failed to store RTC calibration attribute\n");
		return -EINVAL;
	}

	retval = ab8500_rtc_set_calibration(dev, calibration);

	return retval ? retval : count;
}