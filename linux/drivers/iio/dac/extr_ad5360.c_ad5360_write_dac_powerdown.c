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
 int /*<<< orphan*/  AD5360_SF_CTRL_PWR_DOWN ; 
 int ad5360_update_ctrl (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t ad5360_write_dac_powerdown(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool pwr_down;
	int ret;

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	if (pwr_down)
		ret = ad5360_update_ctrl(indio_dev, AD5360_SF_CTRL_PWR_DOWN, 0);
	else
		ret = ad5360_update_ctrl(indio_dev, 0, AD5360_SF_CTRL_PWR_DOWN);

	return ret ? ret : len;
}