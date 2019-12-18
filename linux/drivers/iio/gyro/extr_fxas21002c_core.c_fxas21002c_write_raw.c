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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct fxas21002c_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FXAS21002C_SCALE_FRACTIONAL ; 
#define  IIO_ANGL_VEL 132 
#define  IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY 131 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int fxas21002c_hpf_set (struct fxas21002c_data*,int) ; 
 int fxas21002c_lpf_set (struct fxas21002c_data*,int) ; 
 int fxas21002c_odr_set (struct fxas21002c_data*,int) ; 
 int fxas21002c_scale_set (struct fxas21002c_data*,int) ; 
 struct fxas21002c_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int fxas21002c_write_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan, int val,
				int val2, long mask)
{
	struct fxas21002c_data *data = iio_priv(indio_dev);
	int range;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val2)
			return -EINVAL;

		return fxas21002c_odr_set(data, val);
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		if (val)
			return -EINVAL;

		val2 = val2 / 10000;
		return fxas21002c_lpf_set(data, val2);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			range = (((val * 1000 + val2 / 1000) *
				  FXAS21002C_SCALE_FRACTIONAL) / 1000);
			return fxas21002c_scale_set(data, range);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		return fxas21002c_hpf_set(data, val2);
	default:
		return -EINVAL;
	}
}