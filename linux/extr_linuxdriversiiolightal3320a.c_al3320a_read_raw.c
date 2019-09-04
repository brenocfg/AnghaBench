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
struct iio_chan_spec {int dummy; } ;
struct al3320a_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int AL3320A_GAIN_MASK ; 
 int AL3320A_GAIN_SHIFT ; 
 int /*<<< orphan*/  AL3320A_REG_CONFIG_RANGE ; 
 int /*<<< orphan*/  AL3320A_REG_DATA_LOW ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int** al3320a_scales ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct al3320a_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int al3320a_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int *val,
			    int *val2, long mask)
{
	struct al3320a_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/*
		 * ALS ADC value is stored in two adjacent registers:
		 * - low byte of output is stored at AL3320A_REG_DATA_LOW
		 * - high byte of output is stored at AL3320A_REG_DATA_LOW + 1
		 */
		ret = i2c_smbus_read_word_data(data->client,
					       AL3320A_REG_DATA_LOW);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_read_byte_data(data->client,
					       AL3320A_REG_CONFIG_RANGE);
		if (ret < 0)
			return ret;

		ret = (ret & AL3320A_GAIN_MASK) >> AL3320A_GAIN_SHIFT;
		*val = al3320a_scales[ret][0];
		*val2 = al3320a_scales[ret][1];

		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}