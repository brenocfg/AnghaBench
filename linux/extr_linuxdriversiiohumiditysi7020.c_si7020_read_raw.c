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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_HUMIDITYRELATIVE ; 
 int /*<<< orphan*/  IIO_TEMP ; 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  SI7020CMD_RH_HOLD ; 
 int /*<<< orphan*/  SI7020CMD_TEMP_HOLD ; 
 int clamp_val (int,int,int) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client** iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int si7020_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int *val,
			   int *val2, long mask)
{
	struct i2c_client **client = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_read_word_swapped(*client,
						  chan->type == IIO_TEMP ?
						  SI7020CMD_TEMP_HOLD :
						  SI7020CMD_RH_HOLD);
		if (ret < 0)
			return ret;
		*val = ret >> 2;
		/*
		 * Humidity values can slightly exceed the 0-100%RH
		 * range and should be corrected by software
		 */
		if (chan->type == IIO_HUMIDITYRELATIVE)
			*val = clamp_val(*val, 786, 13893);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_TEMP)
			*val = 175720; /* = 175.72 * 1000 */
		else
			*val = 125 * 1000;
		*val2 = 65536 >> 2;
		return IIO_VAL_FRACTIONAL;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * Since iio_convert_raw_to_processed_unlocked assumes offset
		 * is an integer we have to round these values and lose
		 * accuracy.
		 * Relative humidity will be 0.0032959% too high and
		 * temperature will be 0.00277344 degrees too high.
		 * This is no big deal because it's within the accuracy of the
		 * sensor.
		 */
		if (chan->type == IIO_TEMP)
			*val = -4368; /* = -46.85 * (65536 >> 2) / 175.72 */
		else
			*val = -786; /* = -6 * (65536 >> 2) / 125 */
		return IIO_VAL_INT;
	default:
		break;
	}

	return -EINVAL;
}