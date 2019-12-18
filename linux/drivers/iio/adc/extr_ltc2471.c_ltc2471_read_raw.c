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
struct ltc2471_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  differential; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int LTC2471_VREF ; 
 struct ltc2471_data* iio_priv (struct iio_dev*) ; 
 int ltc2471_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2471_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long info)
{
	struct ltc2471_data *data = iio_priv(indio_dev);
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		ret = ltc2471_get_value(data->client);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		if (chan->differential)
			/* Output ranges from -VREF to +VREF */
			*val = 2 * LTC2471_VREF;
		else
			/* Output ranges from 0 to VREF */
			*val = LTC2471_VREF;
		*val2 = 16;	/* 16 data bits */
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_OFFSET:
		/* Only differential chip has this property */
		*val = -LTC2471_VREF;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}