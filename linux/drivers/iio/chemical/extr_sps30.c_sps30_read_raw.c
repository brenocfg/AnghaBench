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
struct sps30_state {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 134 
#define  IIO_CHAN_INFO_SCALE 133 
#define  IIO_MASSCONCENTRATION 132 
#define  IIO_MOD_PM1 131 
#define  IIO_MOD_PM10 130 
#define  IIO_MOD_PM2P5 129 
#define  IIO_MOD_PM4 128 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct sps30_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sps30_do_meas (struct sps30_state*,int*,int) ; 

__attribute__((used)) static int sps30_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val, int *val2, long mask)
{
	struct sps30_state *state = iio_priv(indio_dev);
	int data[4], ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_MASSCONCENTRATION:
			mutex_lock(&state->lock);
			/* read up to the number of bytes actually needed */
			switch (chan->channel2) {
			case IIO_MOD_PM1:
				ret = sps30_do_meas(state, data, 1);
				break;
			case IIO_MOD_PM2P5:
				ret = sps30_do_meas(state, data, 2);
				break;
			case IIO_MOD_PM4:
				ret = sps30_do_meas(state, data, 3);
				break;
			case IIO_MOD_PM10:
				ret = sps30_do_meas(state, data, 4);
				break;
			}
			mutex_unlock(&state->lock);
			if (ret)
				return ret;

			*val = data[chan->address] / 100;
			*val2 = (data[chan->address] % 100) * 10000;

			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_MASSCONCENTRATION:
			switch (chan->channel2) {
			case IIO_MOD_PM1:
			case IIO_MOD_PM2P5:
			case IIO_MOD_PM4:
			case IIO_MOD_PM10:
				*val = 0;
				*val2 = 10000;

				return IIO_VAL_INT_PLUS_MICRO;
			default:
				return -EINVAL;
			}
		default:
			return -EINVAL;
		}
	}

	return -EINVAL;
}