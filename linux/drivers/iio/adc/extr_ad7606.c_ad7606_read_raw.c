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
struct ad7606_state {int* scale_avail; size_t* range; int oversampling; int /*<<< orphan*/  sw_mode_en; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int ad7606_scan_direct (struct iio_dev*,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7606_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	int ret, ch = 0;
	struct ad7606_state *st = iio_priv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		ret = ad7606_scan_direct(indio_dev, chan->address);
		iio_device_release_direct_mode(indio_dev);

		if (ret < 0)
			return ret;
		*val = (short)ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (st->sw_mode_en)
			ch = chan->address;
		*val = 0;
		*val2 = st->scale_avail[st->range[ch]];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = st->oversampling;
		return IIO_VAL_INT;
	}
	return -EINVAL;
}