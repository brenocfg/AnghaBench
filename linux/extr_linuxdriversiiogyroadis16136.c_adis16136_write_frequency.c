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
struct adis16136 {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int adis16136_set_freq (struct adis16136*,unsigned int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adis16136* iio_priv (struct iio_dev*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 

__attribute__((used)) static ssize_t adis16136_write_frequency(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct adis16136 *adis16136 = iio_priv(indio_dev);
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 10, &val);
	if (ret)
		return ret;

	if (val == 0)
		return -EINVAL;

	ret = adis16136_set_freq(adis16136, val);

	return ret ? ret : len;
}