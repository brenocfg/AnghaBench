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
struct sx9500_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_PROXIMITY 128 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int sx9500_set_samp_freq (struct sx9500_data*,int,int) ; 

__attribute__((used)) static int sx9500_write_raw(struct iio_dev *indio_dev,
			    const struct iio_chan_spec *chan,
			    int val, int val2, long mask)
{
	struct sx9500_data *data = iio_priv(indio_dev);

	switch (chan->type) {
	case IIO_PROXIMITY:
		switch (mask) {
		case IIO_CHAN_INFO_SAMP_FREQ:
			return sx9500_set_samp_freq(data, val, val2);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}