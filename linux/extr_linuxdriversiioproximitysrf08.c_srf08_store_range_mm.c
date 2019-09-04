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
struct srf08_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct srf08_data* iio_priv (struct iio_dev*) ; 
 int iio_str_to_fixpoint (char const*,int,int*,int*) ; 
 int srf08_write_range_mm (struct srf08_data*,int) ; 

__attribute__((used)) static ssize_t srf08_store_range_mm(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct srf08_data *data = iio_priv(indio_dev);
	int ret;
	int integer, fract;

	ret = iio_str_to_fixpoint(buf, 100, &integer, &fract);
	if (ret)
		return ret;

	ret = srf08_write_range_mm(data, integer * 1000 + fract);
	if (ret < 0)
		return ret;

	return len;
}