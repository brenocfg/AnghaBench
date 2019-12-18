#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ina2xx_chip_info {int avg; int int_time_vshunt; int int_time_vbus; int shunt_resistor_uohm; int pga_gain_vshunt; int range_vbus; TYPE_1__* config; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; } ;
typedef  int s16 ;
struct TYPE_2__ {int bus_voltage_shift; int shunt_voltage_lsb; int bus_voltage_lsb; int power_lsb_factor; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 137 
#define  IIO_CHAN_INFO_INT_TIME 136 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 135 
#define  IIO_CHAN_INFO_RAW 134 
#define  IIO_CHAN_INFO_SAMP_FREQ 133 
#define  IIO_CHAN_INFO_SCALE 132 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  INA2XX_BUS_VOLTAGE 131 
#define  INA2XX_CURRENT 130 
#define  INA2XX_POWER 129 
#define  INA2XX_SHUNT_VOLTAGE 128 
 int /*<<< orphan*/  SAMPLING_PERIOD (struct ina2xx_chip_info*) ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  is_signed_reg (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int ina2xx_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret;
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);
	unsigned int regval;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = regmap_read(chip->regmap, chan->address, &regval);
		if (ret)
			return ret;

		if (is_signed_reg(chan->address))
			*val = (s16) regval;
		else
			*val  = regval;

		if (chan->address == INA2XX_BUS_VOLTAGE)
			*val >>= chip->config->bus_voltage_shift;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = chip->avg;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		if (chan->address == INA2XX_SHUNT_VOLTAGE)
			*val2 = chip->int_time_vshunt;
		else
			*val2 = chip->int_time_vbus;

		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		/*
		 * Sample freq is read only, it is a consequence of
		 * 1/AVG*(CT_bus+CT_shunt).
		 */
		*val = DIV_ROUND_CLOSEST(1000000, SAMPLING_PERIOD(chip));

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->address) {
		case INA2XX_SHUNT_VOLTAGE:
			/* processed (mV) = raw * lsb(nV) / 1000000 */
			*val = chip->config->shunt_voltage_lsb;
			*val2 = 1000000;
			return IIO_VAL_FRACTIONAL;

		case INA2XX_BUS_VOLTAGE:
			/* processed (mV) = raw * lsb (uV) / 1000 */
			*val = chip->config->bus_voltage_lsb;
			*val2 = 1000;
			return IIO_VAL_FRACTIONAL;

		case INA2XX_CURRENT:
			/*
			 * processed (mA) = raw * current_lsb (mA)
			 * current_lsb (mA) = shunt_voltage_lsb (nV) /
			 *                    shunt_resistor (uOhm)
			 */
			*val = chip->config->shunt_voltage_lsb;
			*val2 = chip->shunt_resistor_uohm;
			return IIO_VAL_FRACTIONAL;

		case INA2XX_POWER:
			/*
			 * processed (mW) = raw * power_lsb (mW)
			 * power_lsb (mW) = power_lsb_factor (mW/mA) *
			 *                  current_lsb (mA)
			 */
			*val = chip->config->power_lsb_factor *
			       chip->config->shunt_voltage_lsb;
			*val2 = chip->shunt_resistor_uohm;
			return IIO_VAL_FRACTIONAL;
		}
		return -EINVAL;

	case IIO_CHAN_INFO_HARDWAREGAIN:
		switch (chan->address) {
		case INA2XX_SHUNT_VOLTAGE:
			*val = chip->pga_gain_vshunt;
			*val2 = 1000;
			return IIO_VAL_FRACTIONAL;

		case INA2XX_BUS_VOLTAGE:
			*val = chip->range_vbus == 32 ? 1 : 2;
			return IIO_VAL_INT;
		}
		return -EINVAL;
	}

	return -EINVAL;
}