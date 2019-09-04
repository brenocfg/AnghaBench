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
struct iio_dummy_state {int dac_val; int* differential_adc_val; int single_ended_adc_val; int accel_val; int steps; int activity_running; int activity_walking; int accel_calibbias; int steps_enabled; int height; int /*<<< orphan*/  lock; TYPE_1__* accel_calibscale; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; int /*<<< orphan*/  type; int /*<<< orphan*/  differential; int /*<<< orphan*/  channel2; int /*<<< orphan*/  output; } ;
struct TYPE_2__ {int val; int val2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 142 
#define  IIO_ACTIVITY 141 
#define  IIO_CHAN_INFO_CALIBBIAS 140 
#define  IIO_CHAN_INFO_CALIBHEIGHT 139 
#define  IIO_CHAN_INFO_CALIBSCALE 138 
#define  IIO_CHAN_INFO_ENABLE 137 
#define  IIO_CHAN_INFO_OFFSET 136 
#define  IIO_CHAN_INFO_PROCESSED 135 
#define  IIO_CHAN_INFO_RAW 134 
#define  IIO_CHAN_INFO_SAMP_FREQ 133 
#define  IIO_CHAN_INFO_SCALE 132 
#define  IIO_MOD_RUNNING 131 
#define  IIO_MOD_WALKING 130 
#define  IIO_STEPS 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_dummy_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val,
			      int *val2,
			      long mask)
{
	struct iio_dummy_state *st = iio_priv(indio_dev);
	int ret = -EINVAL;

	mutex_lock(&st->lock);
	switch (mask) {
	case IIO_CHAN_INFO_RAW: /* magic value - channel value read */
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->output) {
				/* Set integer part to cached value */
				*val = st->dac_val;
				ret = IIO_VAL_INT;
			} else if (chan->differential) {
				if (chan->channel == 1)
					*val = st->differential_adc_val[0];
				else
					*val = st->differential_adc_val[1];
				ret = IIO_VAL_INT;
			} else {
				*val = st->single_ended_adc_val;
				ret = IIO_VAL_INT;
			}
			break;
		case IIO_ACCEL:
			*val = st->accel_val;
			ret = IIO_VAL_INT;
			break;
		default:
			break;
		}
		break;
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			*val = st->steps;
			ret = IIO_VAL_INT;
			break;
		case IIO_ACTIVITY:
			switch (chan->channel2) {
			case IIO_MOD_RUNNING:
				*val = st->activity_running;
				ret = IIO_VAL_INT;
				break;
			case IIO_MOD_WALKING:
				*val = st->activity_walking;
				ret = IIO_VAL_INT;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case IIO_CHAN_INFO_OFFSET:
		/* only single ended adc -> 7 */
		*val = 7;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			switch (chan->differential) {
			case 0:
				/* only single ended adc -> 0.001333 */
				*val = 0;
				*val2 = 1333;
				ret = IIO_VAL_INT_PLUS_MICRO;
				break;
			case 1:
				/* all differential adc -> 0.000001344 */
				*val = 0;
				*val2 = 1344;
				ret = IIO_VAL_INT_PLUS_NANO;
			}
			break;
		default:
			break;
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		/* only the acceleration axis - read from cache */
		*val = st->accel_calibbias;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		*val = st->accel_calibscale->val;
		*val2 = st->accel_calibscale->val2;
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = 3;
		*val2 = 33;
		ret = IIO_VAL_INT_PLUS_NANO;
		break;
	case IIO_CHAN_INFO_ENABLE:
		switch (chan->type) {
		case IIO_STEPS:
			*val = st->steps_enabled;
			ret = IIO_VAL_INT;
			break;
		default:
			break;
		}
		break;
	case IIO_CHAN_INFO_CALIBHEIGHT:
		switch (chan->type) {
		case IIO_STEPS:
			*val = st->height;
			ret = IIO_VAL_INT;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	mutex_unlock(&st->lock);
	return ret;
}