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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  als_cal_target; } ;
struct tsl2772_chip {TYPE_1__ settings; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 scalar_t__ kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tsl2772_invoke_change (struct iio_dev*) ; 

__attribute__((used)) static ssize_t in_illuminance0_target_input_store(struct device *dev,
						  struct device_attribute *attr,
						  const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	u16 value;
	int ret;

	if (kstrtou16(buf, 0, &value))
		return -EINVAL;

	chip->settings.als_cal_target = value;
	ret = tsl2772_invoke_change(indio_dev);
	if (ret < 0)
		return ret;

	return len;
}