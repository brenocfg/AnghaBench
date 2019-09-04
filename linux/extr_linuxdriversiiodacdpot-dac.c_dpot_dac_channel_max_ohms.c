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
struct device {int dummy; } ;
struct iio_dev {struct device dev; } ;
struct dpot_dac {int /*<<< orphan*/  dpot; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_VAL_FRACTIONAL 130 
#define  IIO_VAL_FRACTIONAL_LOG2 129 
#define  IIO_VAL_INT 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,long long) ; 
 struct dpot_dac* iio_priv (struct iio_dev*) ; 
 int iio_read_channel_scale (int /*<<< orphan*/ ,int*,int*) ; 
 int iio_read_max_channel_raw (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int dpot_dac_channel_max_ohms(struct iio_dev *indio_dev)
{
	struct device *dev = &indio_dev->dev;
	struct dpot_dac *dac = iio_priv(indio_dev);
	unsigned long long tmp;
	int ret;
	int val;
	int val2;
	int max;

	ret = iio_read_max_channel_raw(dac->dpot, &max);
	if (ret < 0) {
		dev_err(dev, "dpot does not indicate its raw maximum value\n");
		return ret;
	}

	switch (iio_read_channel_scale(dac->dpot, &val, &val2)) {
	case IIO_VAL_INT:
		return max * val;
	case IIO_VAL_FRACTIONAL:
		tmp = (unsigned long long)max * val;
		do_div(tmp, val2);
		return tmp;
	case IIO_VAL_FRACTIONAL_LOG2:
		tmp = val * 1000000000LL * max >> val2;
		do_div(tmp, 1000000000LL);
		return tmp;
	default:
		dev_err(dev, "dpot has a scale that is too weird\n");
	}

	return -EINVAL;
}