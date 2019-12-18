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
struct adc081c {int bits; int /*<<< orphan*/  ref; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  REG_CONV_RES ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adc081c* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc081c_read_raw(struct iio_dev *iio,
			    struct iio_chan_spec const *channel, int *value,
			    int *shift, long mask)
{
	struct adc081c *adc = iio_priv(iio);
	int err;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		err = i2c_smbus_read_word_swapped(adc->i2c, REG_CONV_RES);
		if (err < 0)
			return err;

		*value = (err & 0xFFF) >> (12 - adc->bits);
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		err = regulator_get_voltage(adc->ref);
		if (err < 0)
			return err;

		*value = err / 1000;
		*shift = adc->bits;

		return IIO_VAL_FRACTIONAL_LOG2;

	default:
		break;
	}

	return -EINVAL;
}