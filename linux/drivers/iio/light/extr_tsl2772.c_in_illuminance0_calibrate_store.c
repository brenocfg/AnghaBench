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
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 int tsl2772_als_calibrate (struct iio_dev*) ; 
 int tsl2772_invoke_change (struct iio_dev*) ; 

__attribute__((used)) static ssize_t in_illuminance0_calibrate_store(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool value;
	int ret;

	if (kstrtobool(buf, &value) || !value)
		return -EINVAL;

	ret = tsl2772_als_calibrate(indio_dev);
	if (ret < 0)
		return ret;

	ret = tsl2772_invoke_change(indio_dev);
	if (ret < 0)
		return ret;

	return len;
}