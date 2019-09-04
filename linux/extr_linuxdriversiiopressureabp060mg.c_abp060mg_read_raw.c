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
struct iio_chan_spec {int dummy; } ;
struct abp_state {int offset; int scale; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ABP060MG_NUM_COUNTS ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int abp060mg_get_measurement (struct abp_state*,int*) ; 
 struct abp_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int abp060mg_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan, int *val,
			int *val2, long mask)
{
	struct abp_state *state = iio_priv(indio_dev);
	int ret;

	mutex_lock(&state->lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = abp060mg_get_measurement(state, val);
		break;
	case IIO_CHAN_INFO_OFFSET:
		*val = state->offset;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = state->scale;
		*val2 = ABP060MG_NUM_COUNTS * 1000; /* to kPa */
		ret = IIO_VAL_FRACTIONAL;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&state->lock);
	return ret;
}