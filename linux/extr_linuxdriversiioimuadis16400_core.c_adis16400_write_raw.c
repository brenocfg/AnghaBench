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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t scan_index; } ;
struct adis16400_state {int filt_int; TYPE_1__* variant; int /*<<< orphan*/  adis; } ;
struct TYPE_2__ {int (* get_freq ) (struct adis16400_state*) ;int (* set_freq ) (struct adis16400_state*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/ * adis16400_addresses ; 
 int adis16400_set_filter (struct iio_dev*,int,int) ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adis16400_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct adis16400_state*) ; 
 int stub2 (struct adis16400_state*,int) ; 

__attribute__((used)) static int adis16400_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	struct adis16400_state *st = iio_priv(indio_dev);
	int ret, sps;

	switch (info) {
	case IIO_CHAN_INFO_CALIBBIAS:
		mutex_lock(&indio_dev->mlock);
		ret = adis_write_reg_16(&st->adis,
				adis16400_addresses[chan->scan_index], val);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		/*
		 * Need to cache values so we can update if the frequency
		 * changes.
		 */
		mutex_lock(&indio_dev->mlock);
		st->filt_int = val;
		/* Work out update to current value */
		sps = st->variant->get_freq(st);
		if (sps < 0) {
			mutex_unlock(&indio_dev->mlock);
			return sps;
		}

		ret = adis16400_set_filter(indio_dev, sps,
			val * 1000 + val2 / 1000);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	case IIO_CHAN_INFO_SAMP_FREQ:
		sps = val * 1000 + val2 / 1000;

		if (sps <= 0)
			return -EINVAL;

		mutex_lock(&indio_dev->mlock);
		ret = st->variant->set_freq(st, sps);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	default:
		return -EINVAL;
	}
}