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
struct si7005_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_TEMP ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct si7005_data* iio_priv (struct iio_dev*) ; 
 int si7005_read_measurement (struct si7005_data*,int) ; 

__attribute__((used)) static int si7005_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int *val,
			    int *val2, long mask)
{
	struct si7005_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = si7005_read_measurement(data, chan->type == IIO_TEMP);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_TEMP) {
			*val = 7;
			*val2 = 812500;
		} else {
			*val = 3;
			*val2 = 906250;
		}
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP)
			*val = -50 * 32 * 4;
		else
			*val = -24 * 16 * 16;
		return IIO_VAL_INT;
	default:
		break;
	}

	return -EINVAL;
}