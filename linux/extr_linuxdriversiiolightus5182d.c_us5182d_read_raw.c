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
struct us5182d_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int US5182D_AGAIN_MASK ; 
 int /*<<< orphan*/  US5182D_REG_CFG1 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int us5182d_read_value (struct us5182d_data*,struct iio_chan_spec const*) ; 
 int* us5182d_scales ; 

__attribute__((used)) static int us5182d_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int *val,
			    int *val2, long mask)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = us5182d_read_value(data, chan);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CFG1);
		if (ret < 0)
			return ret;
		*val = 0;
		*val2 = us5182d_scales[ret & US5182D_AGAIN_MASK];
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}