#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ms5611_state {int /*<<< orphan*/  lock; TYPE_2__* pressure_osr; TYPE_1__* temp_osr; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int const type; } ;
typedef  int s32 ;
struct TYPE_4__ {scalar_t__ rate; } ;
struct TYPE_3__ {scalar_t__ rate; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 132 
#define  IIO_CHAN_INFO_PROCESSED 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int ms5611_read_temp_and_pressure (struct iio_dev*,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms5611_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret;
	s32 temp, pressure;
	struct ms5611_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&st->lock);
		ret = ms5611_read_temp_and_pressure(indio_dev,
						    &temp, &pressure);
		mutex_unlock(&st->lock);
		if (ret < 0)
			return ret;

		switch (chan->type) {
		case IIO_TEMP:
			*val = temp * 10;
			return IIO_VAL_INT;
		case IIO_PRESSURE:
			*val = pressure / 1000;
			*val2 = (pressure % 1000) * 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_TEMP:
			*val = 10;
			return IIO_VAL_INT;
		case IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		if (chan->type != IIO_TEMP && chan->type != IIO_PRESSURE)
			break;
		mutex_lock(&st->lock);
		if (chan->type == IIO_TEMP)
			*val = (int)st->temp_osr->rate;
		else
			*val = (int)st->pressure_osr->rate;
		mutex_unlock(&st->lock);
		return IIO_VAL_INT;
	}

	return -EINVAL;
}