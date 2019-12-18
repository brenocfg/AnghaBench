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
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_COARSE ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_RAW ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  CLOCK_REALTIME_COARSE ; 
 int /*<<< orphan*/  CLOCK_TAI ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 int iio_device_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t iio_store_timestamp_clock(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t len)
{
	clockid_t clk;
	int ret;

	if (sysfs_streq(buf, "realtime"))
		clk = CLOCK_REALTIME;
	else if (sysfs_streq(buf, "monotonic"))
		clk = CLOCK_MONOTONIC;
	else if (sysfs_streq(buf, "monotonic_raw"))
		clk = CLOCK_MONOTONIC_RAW;
	else if (sysfs_streq(buf, "realtime_coarse"))
		clk = CLOCK_REALTIME_COARSE;
	else if (sysfs_streq(buf, "monotonic_coarse"))
		clk = CLOCK_MONOTONIC_COARSE;
	else if (sysfs_streq(buf, "boottime"))
		clk = CLOCK_BOOTTIME;
	else if (sysfs_streq(buf, "tai"))
		clk = CLOCK_TAI;
	else
		return -EINVAL;

	ret = iio_device_set_clock(dev_to_iio_dev(dev), clk);
	if (ret)
		return ret;

	return len;
}