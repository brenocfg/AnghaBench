#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct zopt2201_data {size_t res; size_t gain; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; } ;
struct TYPE_6__ {int scale; } ;
struct TYPE_5__ {int gain; int scale; } ;
struct TYPE_4__ {int us; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 133 
#define  IIO_CHAN_INFO_PROCESSED 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  ZOPT2201_ALS_DATA 129 
#define  ZOPT2201_UVB_DATA 128 
 int /*<<< orphan*/  div_s64 (int,int) ; 
 int div_s64_rem (int /*<<< orphan*/ ,int,int*) ; 
 struct zopt2201_data* iio_priv (struct iio_dev*) ; 
 TYPE_3__* zopt2201_gain_als ; 
 TYPE_2__* zopt2201_gain_uvb ; 
 int zopt2201_read (struct zopt2201_data*,int) ; 
 TYPE_1__* zopt2201_resolution ; 

__attribute__((used)) static int zopt2201_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct zopt2201_data *data = iio_priv(indio_dev);
	u64 tmp;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = zopt2201_read(data, chan->address);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_PROCESSED:
		ret = zopt2201_read(data, ZOPT2201_UVB_DATA);
		if (ret < 0)
			return ret;
		*val = ret * 18 *
			(1 << (20 - zopt2201_resolution[data->res].bits)) /
			zopt2201_gain_uvb[data->gain].gain;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->address) {
		case ZOPT2201_ALS_DATA:
			*val = zopt2201_gain_als[data->gain].scale;
			break;
		case ZOPT2201_UVB_DATA:
			*val = zopt2201_gain_uvb[data->gain].scale;
			break;
		default:
			return -EINVAL;
		}

		*val2 = 1000000;
		*val2 *= (1 << (zopt2201_resolution[data->res].bits - 13));
		tmp = div_s64(*val * 1000000ULL, *val2);
		*val = div_s64_rem(tmp, 1000000, val2);

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = zopt2201_resolution[data->res].us;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}