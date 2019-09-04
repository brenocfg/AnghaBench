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
typedef  int u8 ;
typedef  int u32 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t channel; } ;
struct ad8366_state {unsigned int* ch; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 128 
 int ad8366_write (struct iio_dev*,unsigned int,unsigned int) ; 
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
	unsigned code;
	int ret;

	if (val < 0 || val2 < 0)
		return -EINVAL;

	/* Values in dB */
	code = (((u8)val * 1000) + ((u32)val2 / 1000));

	if (code > 20500 || code < 4500)
		return -EINVAL;

	code = (code - 4500) / 253;

	mutex_lock(&indio_dev->mlock);
	switch (mask) {
	case IIO_CHAN_INFO_HARDWAREGAIN:
		st->ch[chan->channel] = code;
		ret = ad8366_write(indio_dev, st->ch[0], st->ch[1]);
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret;
}