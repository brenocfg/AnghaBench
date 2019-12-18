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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
struct ads8688_state {size_t* range; int vref_mv; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int offset; int scale; size_t range; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 size_t ADS8688_PLUSMINUS25VREF ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 129 
#define  IIO_CHAN_INFO_SCALE 128 
 TYPE_1__* ads8688_range_def ; 
 int ads8688_write_reg_range (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ) ; 
 struct ads8688_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads8688_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct ads8688_state *st = iio_priv(indio_dev);
	unsigned int scale = 0;
	int ret = -EINVAL, i, offset = 0;

	mutex_lock(&st->lock);
	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		/* If the offset is 0 the ±2.5 * VREF mode is not available */
		offset = ads8688_range_def[st->range[chan->channel]].offset;
		if (offset == 0 && val2 == ads8688_range_def[0].scale * st->vref_mv) {
			mutex_unlock(&st->lock);
			return -EINVAL;
		}

		/* Lookup new mode */
		for (i = 0; i < ARRAY_SIZE(ads8688_range_def); i++)
			if (val2 == ads8688_range_def[i].scale * st->vref_mv &&
			    offset == ads8688_range_def[i].offset) {
				ret = ads8688_write_reg_range(indio_dev, chan,
					ads8688_range_def[i].reg);
				break;
			}
		break;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * There are only two available offsets:
		 * 0 and -(1 << (ADS8688_REALBITS - 1))
		 */
		if (!(ads8688_range_def[0].offset == val ||
		    ads8688_range_def[3].offset == val)) {
			mutex_unlock(&st->lock);
			return -EINVAL;
		}

		/*
		 * If the device are in ±2.5 * VREF mode, it's not allowed to
		 * switch to a mode where the offset is 0
		 */
		if (val == 0 &&
		    st->range[chan->channel] == ADS8688_PLUSMINUS25VREF) {
			mutex_unlock(&st->lock);
			return -EINVAL;
		}

		scale = ads8688_range_def[st->range[chan->channel]].scale;

		/* Lookup new mode */
		for (i = 0; i < ARRAY_SIZE(ads8688_range_def); i++)
			if (val == ads8688_range_def[i].offset &&
			    scale == ads8688_range_def[i].scale) {
				ret = ads8688_write_reg_range(indio_dev, chan,
					ads8688_range_def[i].reg);
				break;
			}
		break;
	}

	if (!ret)
		st->range[chan->channel] = ads8688_range_def[i].range;

	mutex_unlock(&st->lock);

	return ret;
}