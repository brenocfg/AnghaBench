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
struct iio_dev_attr {int address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7280_state {long cell_threshhigh; long cell_threshlow; long aux_threshhigh; long aux_threshlow; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  AD7280A_AUX_ADC_OVERVOLTAGE 131 
#define  AD7280A_AUX_ADC_UNDERVOLTAGE 130 
#define  AD7280A_CELL_OVERVOLTAGE 129 
#define  AD7280A_CELL_UNDERVOLTAGE 128 
 int /*<<< orphan*/  AD7280A_DEVADDR_MASTER ; 
 int EFAULT ; 
 int ad7280_write (struct ad7280_state*,int /*<<< orphan*/ ,int,int,long) ; 
 long clamp (long,long,int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7280_write_channel_config(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf,
					   size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7280_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	long val;
	int ret;

	ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	switch (this_attr->address) {
	case AD7280A_CELL_OVERVOLTAGE:
	case AD7280A_CELL_UNDERVOLTAGE:
		val = ((val - 1000) * 100) / 1568; /* LSB 15.68mV */
		break;
	case AD7280A_AUX_ADC_OVERVOLTAGE:
	case AD7280A_AUX_ADC_UNDERVOLTAGE:
		val = (val * 10) / 196; /* LSB 19.6mV */
		break;
	default:
		return -EFAULT;
	}

	val = clamp(val, 0L, 0xFFL);

	mutex_lock(&st->lock);
	switch (this_attr->address) {
	case AD7280A_CELL_OVERVOLTAGE:
		st->cell_threshhigh = val;
		break;
	case AD7280A_CELL_UNDERVOLTAGE:
		st->cell_threshlow = val;
		break;
	case AD7280A_AUX_ADC_OVERVOLTAGE:
		st->aux_threshhigh = val;
		break;
	case AD7280A_AUX_ADC_UNDERVOLTAGE:
		st->aux_threshlow = val;
		break;
	}

	ret = ad7280_write(st, AD7280A_DEVADDR_MASTER,
			   this_attr->address, 1, val);

	mutex_unlock(&st->lock);

	return ret ? ret : len;
}