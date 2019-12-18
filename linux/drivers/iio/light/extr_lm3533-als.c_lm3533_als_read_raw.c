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
struct iio_chan_spec {int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_AVERAGE_RAW 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CURRENT 129 
#define  IIO_LIGHT 128 
 int IIO_VAL_INT ; 
 int lm3533_als_get_adc (struct iio_dev*,int,int*) ; 
 int lm3533_als_get_current (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lm3533_als_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			ret = lm3533_als_get_adc(indio_dev, false, val);
			break;
		case IIO_CURRENT:
			ret = lm3533_als_get_current(indio_dev, chan->channel,
									val);
			break;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_AVERAGE_RAW:
		ret = lm3533_als_get_adc(indio_dev, true, val);
		break;
	default:
		return -EINVAL;
	}

	if (ret)
		return ret;

	return IIO_VAL_INT;
}