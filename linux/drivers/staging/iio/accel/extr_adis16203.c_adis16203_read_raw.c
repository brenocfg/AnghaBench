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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;
struct adis {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16203_ERROR_ACTIVE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 134 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_INCLI 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 
 int /*<<< orphan*/ * adis16203_addresses ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adis_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int*) ; 
 struct adis* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adis16203_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct adis *st = iio_priv(indio_dev);
	int ret;
	u8 addr;
	s16 val16;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return adis_single_conversion(indio_dev, chan,
				ADIS16203_ERROR_ACTIVE, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->channel == 0) {
				*val = 1;
				*val2 = 220000; /* 1.22 mV */
			} else {
				*val = 0;
				*val2 = 610000; /* 0.61 mV */
			}
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = -470; /* -0.47 C */
			*val2 = 0;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_INCLI:
			*val = 0;
			*val2 = 25000; /* 0.025 degree */
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		*val = 25000 / -470 - 1278; /* 25 C = 1278 */
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16203_addresses[chan->scan_index];
		ret = adis_read_reg_16(st, addr, &val16);
		if (ret)
			return ret;
		*val = sign_extend32(val16, 13);
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}