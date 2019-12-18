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
struct iio_chan_spec {size_t channel; } ;
struct ad8366_state {int type; int* ch; int /*<<< orphan*/  lock; struct ad8366_info* info; } ;
struct ad8366_info {int gain_max; int gain_min; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ID_AD8366 131 
#define  ID_ADA4961 130 
#define  ID_ADL5240 129 
#define  IIO_CHAN_INFO_HARDWAREGAIN 128 
 int ad8366_write (struct iio_dev*,int,int) ; 
 struct ad8366_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad8366_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct ad8366_state *st = iio_priv(indio_dev);
	struct ad8366_info *inf = st->info;
	int code = 0, gain;
	int ret;

	/* Values in dB */
	if (val < 0)
		gain = (val * 1000) - (val2 / 1000);
	else
		gain = (val * 1000) + (val2 / 1000);

	if (gain > inf->gain_max || gain < inf->gain_min)
		return -EINVAL;

	switch (st->type) {
	case ID_AD8366:
		code = (gain - 4500) / 253;
		break;
	case ID_ADA4961:
		code = (15000 - gain) / 1000;
		break;
	case ID_ADL5240:
		code = ((gain - 500 - 20000) / 500) & 0x3F;
		break;
	}

	mutex_lock(&st->lock);
	switch (mask) {
	case IIO_CHAN_INFO_HARDWAREGAIN:
		st->ch[chan->channel] = code;
		ret = ad8366_write(indio_dev, st->ch[0], st->ch[1]);
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&st->lock);

	return ret;
}