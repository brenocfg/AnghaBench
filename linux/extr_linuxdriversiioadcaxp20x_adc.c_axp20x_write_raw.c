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
struct iio_chan_spec {int channel; } ;
struct axp20x_adc_iio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  AXP20X_GPIO0_V 129 
 int /*<<< orphan*/  AXP20X_GPIO10_IN_RANGE ; 
 unsigned int AXP20X_GPIO10_IN_RANGE_GPIO0 ; 
 unsigned int AXP20X_GPIO10_IN_RANGE_GPIO0_VAL (int) ; 
 unsigned int AXP20X_GPIO10_IN_RANGE_GPIO1 ; 
 unsigned int AXP20X_GPIO10_IN_RANGE_GPIO1_VAL (int) ; 
#define  AXP20X_GPIO1_V 128 
 int EINVAL ; 
 long IIO_CHAN_INFO_OFFSET ; 
 struct axp20x_adc_iio* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int axp20x_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int val, int val2,
			    long mask)
{
	struct axp20x_adc_iio *info = iio_priv(indio_dev);
	unsigned int reg, regval;

	/*
	 * The AXP20X PMIC allows the user to choose between 0V and 0.7V offsets
	 * for (independently) GPIO0 and GPIO1 when in ADC mode.
	 */
	if (mask != IIO_CHAN_INFO_OFFSET)
		return -EINVAL;

	if (val != 0 && val != 700000)
		return -EINVAL;

	val = val ? 1 : 0;

	switch (chan->channel) {
	case AXP20X_GPIO0_V:
		reg = AXP20X_GPIO10_IN_RANGE_GPIO0;
		regval = AXP20X_GPIO10_IN_RANGE_GPIO0_VAL(val);
		break;

	case AXP20X_GPIO1_V:
		reg = AXP20X_GPIO10_IN_RANGE_GPIO1;
		regval = AXP20X_GPIO10_IN_RANGE_GPIO1_VAL(val);
		break;

	default:
		return -EINVAL;
	}

	return regmap_update_bits(info->regmap, AXP20X_GPIO10_IN_RANGE, reg,
				  regval);
}