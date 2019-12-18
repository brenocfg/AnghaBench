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
typedef  int u32 ;
struct lpc18xx_dac {int /*<<< orphan*/  vref; scalar_t__ base; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 scalar_t__ LPC18XX_DAC_CR ; 
 int LPC18XX_DAC_CR_VALUE_MASK ; 
 int LPC18XX_DAC_CR_VALUE_SHIFT ; 
 struct lpc18xx_dac* iio_priv (struct iio_dev*) ; 
 int readl (scalar_t__) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_dac_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct lpc18xx_dac *dac = iio_priv(indio_dev);
	u32 reg;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		reg = readl(dac->base + LPC18XX_DAC_CR);
		*val = reg >> LPC18XX_DAC_CR_VALUE_SHIFT;
		*val &= LPC18XX_DAC_CR_VALUE_MASK;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(dac->vref) / 1000;
		*val2 = 10;

		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}