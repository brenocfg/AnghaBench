#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {int odr; TYPE_1__* current_fullscale; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int gain; int gain2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int MCELSIUS_PER_CELSIUS ; 
 int ST_PRESS_MILLI_CELSIUS_OFFSET ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int st_sensors_read_info_raw (struct iio_dev*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int st_press_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *ch, int *val,
							int *val2, long mask)
{
	int err;
	struct st_sensor_data *press_data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		err = st_sensors_read_info_raw(indio_dev, ch, val);
		if (err < 0)
			goto read_error;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (ch->type) {
		case IIO_PRESSURE:
			*val = 0;
			*val2 = press_data->current_fullscale->gain;
			return IIO_VAL_INT_PLUS_NANO;
		case IIO_TEMP:
			*val = MCELSIUS_PER_CELSIUS;
			*val2 = press_data->current_fullscale->gain2;
			return IIO_VAL_FRACTIONAL;
		default:
			err = -EINVAL;
			goto read_error;
		}

	case IIO_CHAN_INFO_OFFSET:
		switch (ch->type) {
		case IIO_TEMP:
			*val = ST_PRESS_MILLI_CELSIUS_OFFSET *
			       press_data->current_fullscale->gain2;
			*val2 = MCELSIUS_PER_CELSIUS;
			break;
		default:
			err = -EINVAL;
			goto read_error;
		}

		return IIO_VAL_FRACTIONAL;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = press_data->odr;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}

read_error:
	return err;
}