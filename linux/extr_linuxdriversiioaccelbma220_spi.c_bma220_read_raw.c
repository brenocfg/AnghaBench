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
typedef  size_t u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct bma220_data {int /*<<< orphan*/  spi_device; } ;

/* Variables and functions */
 int BMA220_DATA_SHIFT ; 
 int BMA220_RANGE_MASK ; 
 int /*<<< orphan*/  BMA220_REG_RANGE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int bma220_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** bma220_scale_table ; 
 struct bma220_data* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int bma220_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret;
	u8 range_idx;
	struct bma220_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = bma220_read_reg(data->spi_device, chan->address);
		if (ret < 0)
			return -EINVAL;
		*val = sign_extend32(ret >> BMA220_DATA_SHIFT, 5);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = bma220_read_reg(data->spi_device, BMA220_REG_RANGE);
		if (ret < 0)
			return ret;
		range_idx = ret & BMA220_RANGE_MASK;
		*val = bma220_scale_table[range_idx][0];
		*val2 = bma220_scale_table[range_idx][1];
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}