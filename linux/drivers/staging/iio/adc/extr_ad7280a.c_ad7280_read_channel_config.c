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
struct ad7280_state {int cell_threshhigh; int cell_threshlow; int aux_threshhigh; int aux_threshlow; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  AD7280A_AUX_ADC_OVERVOLTAGE 131 
#define  AD7280A_AUX_ADC_UNDERVOLTAGE 130 
#define  AD7280A_CELL_OVERVOLTAGE 129 
#define  AD7280A_CELL_UNDERVOLTAGE 128 
 int /*<<< orphan*/  EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7280_read_channel_config(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7280_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned int val;

	switch (this_attr->address) {
	case AD7280A_CELL_OVERVOLTAGE:
		val = 1000 + (st->cell_threshhigh * 1568) / 100;
		break;
	case AD7280A_CELL_UNDERVOLTAGE:
		val = 1000 + (st->cell_threshlow * 1568) / 100;
		break;
	case AD7280A_AUX_ADC_OVERVOLTAGE:
		val = (st->aux_threshhigh * 196) / 10;
		break;
	case AD7280A_AUX_ADC_UNDERVOLTAGE:
		val = (st->aux_threshlow * 196) / 10;
		break;
	default:
		return -EINVAL;
	}

	return sprintf(buf, "%u\n", val);
}