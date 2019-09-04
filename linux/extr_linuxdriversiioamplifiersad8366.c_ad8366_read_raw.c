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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t channel; } ;
struct ad8366_state {unsigned int* ch; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 128 
 int IIO_VAL_INT_PLUS_MICRO_DB ; 
 struct ad8366_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad8366_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad8366_state *st = iio_priv(indio_dev);
	int ret;
	unsigned code;

	mutex_lock(&indio_dev->mlock);
	switch (m) {
	case IIO_CHAN_INFO_HARDWAREGAIN:
		code = st->ch[chan->channel];

		/* Values in dB */
		code = code * 253 + 4500;
		*val = code / 1000;
		*val2 = (code % 1000) * 1000;

		ret = IIO_VAL_INT_PLUS_MICRO_DB;
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret;
}