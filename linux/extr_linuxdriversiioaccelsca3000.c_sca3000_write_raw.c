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
struct sca3000_state {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_write_3db_freq (struct sca3000_state*,int) ; 
 int sca3000_write_raw_samp_freq (struct sca3000_state*,int) ; 

__attribute__((used)) static int sca3000_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val2)
			return -EINVAL;
		mutex_lock(&st->lock);
		ret = sca3000_write_raw_samp_freq(st, val);
		mutex_unlock(&st->lock);
		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		if (val2)
			return -EINVAL;
		mutex_lock(&st->lock);
		ret = sca3000_write_3db_freq(st, val);
		mutex_unlock(&st->lock);
		return ret;
	default:
		return -EINVAL;
	}

	return ret;
}