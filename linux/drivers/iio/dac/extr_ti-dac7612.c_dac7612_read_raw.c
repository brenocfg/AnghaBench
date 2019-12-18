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
struct dac7612 {int* cache; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 struct dac7612* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int dac7612_read_raw(struct iio_dev *iio_dev,
			    const struct iio_chan_spec *chan,
			    int *val, int *val2, long mask)
{
	struct dac7612 *priv;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		priv = iio_priv(iio_dev);
		*val = priv->cache[chan->channel];
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 1;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}