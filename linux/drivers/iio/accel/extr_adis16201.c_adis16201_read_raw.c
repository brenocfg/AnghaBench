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
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;
struct adis {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16201_ERROR_ACTIVE ; 
 int EINVAL ; 
#define  IIO_ACCEL 135 
#define  IIO_CHAN_INFO_CALIBBIAS 134 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
 int IIO_G_TO_M_S_2 (int) ; 
#define  IIO_INCLI 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 int /*<<< orphan*/ * adis16201_addresses ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adis_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int*) ; 
 struct adis* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adis16201_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct adis *st = iio_priv(indio_dev);
	int ret;
	int bits;
	u8 addr;
	s16 val16;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return adis_single_conversion(indio_dev, chan,
					      ADIS16201_ERROR_ACTIVE, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->channel == 0) {
			/* Voltage base units are mV hence 1.22 mV */
				*val = 1;
				*val2 = 220000;
			} else {
			/* Voltage base units are mV hence 0.61 mV */
				*val = 0;
				*val2 = 610000;
			}
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = -470;
			*val2 = 0;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ACCEL:
			/*
			 * IIO base unit for sensitivity of accelerometer
			 * is milli g.
			 * 1 LSB represents 0.244 mg.
			 */
			*val = 0;
			*val2 = IIO_G_TO_M_S_2(462400);
			return IIO_VAL_INT_PLUS_NANO;
		case IIO_INCLI:
			*val = 0;
			*val2 = 100000;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * The raw ADC value is 1278 when the temperature
		 * is 25 degrees and the scale factor per milli
		 * degree celcius is -470.
		 */
		*val = 25000 / -470 - 1278;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		switch (chan->type) {
		case IIO_ACCEL:
			bits = 12;
			break;
		case IIO_INCLI:
			bits = 9;
			break;
		default:
			return -EINVAL;
		}
		addr = adis16201_addresses[chan->scan_index];
		ret = adis_read_reg_16(st, addr, &val16);
		if (ret)
			return ret;

		*val = sign_extend32(val16, bits - 1);
		return IIO_VAL_INT;
	}

	return -EINVAL;
}