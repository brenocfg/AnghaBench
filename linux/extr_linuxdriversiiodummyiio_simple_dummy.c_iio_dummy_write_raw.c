#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dummy_state {int dac_val; int steps; int activity_running; int activity_walking; int accel_calibbias; int steps_enabled; int height; int /*<<< orphan*/  lock; TYPE_1__* accel_calibscale; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel2; int /*<<< orphan*/  output; } ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
#define  IIO_ACTIVITY 138 
#define  IIO_CHAN_INFO_CALIBBIAS 137 
#define  IIO_CHAN_INFO_CALIBHEIGHT 136 
#define  IIO_CHAN_INFO_CALIBSCALE 135 
#define  IIO_CHAN_INFO_ENABLE 134 
#define  IIO_CHAN_INFO_PROCESSED 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_MOD_RUNNING 131 
#define  IIO_MOD_WALKING 130 
#define  IIO_STEPS 129 
#define  IIO_VOLTAGE 128 
 TYPE_1__* dummy_scales ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_dummy_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	int i;
	int ret = 0;
	struct iio_dummy_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->output == 0)
				return -EINVAL;

			/* Locking not required as writing single value */
			mutex_lock(&st->lock);
			st->dac_val = val;
			mutex_unlock(&st->lock);
			return 0;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			mutex_lock(&st->lock);
			st->steps = val;
			mutex_unlock(&st->lock);
			return 0;
		case IIO_ACTIVITY:
			if (val < 0)
				val = 0;
			if (val > 100)
				val = 100;
			switch (chan->channel2) {
			case IIO_MOD_RUNNING:
				st->activity_running = val;
				return 0;
			case IIO_MOD_WALKING:
				st->activity_walking = val;
				return 0;
			default:
				return -EINVAL;
			}
			break;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_CALIBSCALE:
		mutex_lock(&st->lock);
		/* Compare against table - hard matching here */
		for (i = 0; i < ARRAY_SIZE(dummy_scales); i++)
			if (val == dummy_scales[i].val &&
			    val2 == dummy_scales[i].val2)
				break;
		if (i == ARRAY_SIZE(dummy_scales))
			ret = -EINVAL;
		else
			st->accel_calibscale = &dummy_scales[i];
		mutex_unlock(&st->lock);
		return ret;
	case IIO_CHAN_INFO_CALIBBIAS:
		mutex_lock(&st->lock);
		st->accel_calibbias = val;
		mutex_unlock(&st->lock);
		return 0;
	case IIO_CHAN_INFO_ENABLE:
		switch (chan->type) {
		case IIO_STEPS:
			mutex_lock(&st->lock);
			st->steps_enabled = val;
			mutex_unlock(&st->lock);
			return 0;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_CALIBHEIGHT:
		switch (chan->type) {
		case IIO_STEPS:
			st->height = val;
			return 0;
		default:
			return -EINVAL;
		}

	default:
		return -EINVAL;
	}
}