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
struct iio_chan_spec {int address; } ;
struct ad7280_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  scan_cnt; } ;

/* Variables and functions */
 int AD7280A_ALL_CELLS ; 
 int AD7280A_BITS ; 
 int AD7280A_CELL_VOLTAGE_6 ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad7280_read_all_channels (struct ad7280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ad7280_read_channel (struct ad7280_state*,int,int) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7280_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad7280_state *st = iio_priv(indio_dev);
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		if (chan->address == AD7280A_ALL_CELLS)
			ret = ad7280_read_all_channels(st, st->scan_cnt, NULL);
		else
			ret = ad7280_read_channel(st, chan->address >> 8,
						  chan->address & 0xFF);
		mutex_unlock(&st->lock);

		if (ret < 0)
			return ret;

		*val = ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if ((chan->address & 0xFF) <= AD7280A_CELL_VOLTAGE_6)
			*val = 4000;
		else
			*val = 5000;

		*val2 = AD7280A_BITS;
		return IIO_VAL_FRACTIONAL_LOG2;
	}
	return -EINVAL;
}