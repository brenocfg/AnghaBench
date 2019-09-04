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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
struct ads8688_state {unsigned long vref_mv; size_t* range; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned long scale; int offset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 TYPE_1__* ads8688_range_def ; 
 int ads8688_read (struct iio_dev*,size_t) ; 
 struct ads8688_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads8688_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long m)
{
	int ret, offset;
	unsigned long scale_mv;

	struct ads8688_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ads8688_read(indio_dev, chan->channel);
		mutex_unlock(&st->lock);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		scale_mv = st->vref_mv;
		scale_mv *= ads8688_range_def[st->range[chan->channel]].scale;
		*val = 0;
		*val2 = scale_mv;
		mutex_unlock(&st->lock);
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		offset = ads8688_range_def[st->range[chan->channel]].offset;
		*val = offset;
		mutex_unlock(&st->lock);
		return IIO_VAL_INT;
	}
	mutex_unlock(&st->lock);

	return -EINVAL;
}