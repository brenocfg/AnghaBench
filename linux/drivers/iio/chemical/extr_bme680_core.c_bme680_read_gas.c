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
typedef  unsigned int u8 ;
typedef  int u16 ;
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int BME680_ADC_GAS_RES_SHIFT ; 
 unsigned int BME680_GAS_MEAS_BIT ; 
 unsigned int BME680_GAS_RANGE_MASK ; 
 unsigned int BME680_GAS_STAB_BIT ; 
 int /*<<< orphan*/  BME680_REG_GAS_MSB ; 
 int /*<<< orphan*/  BME680_REG_GAS_R_LSB ; 
 int /*<<< orphan*/  BME680_REG_MEAS_STAT_0 ; 
 int EBUSY ; 
 int EINVAL ; 
 int IIO_VAL_INT ; 
 int be16_to_cpu (scalar_t__) ; 
 int bme680_compensate_gas (struct bme680_data*,int,unsigned int) ; 
 int bme680_gas_config (struct bme680_data*) ; 
 int bme680_set_mode (struct bme680_data*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bme680_read_gas(struct bme680_data *data,
			   int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	__be16 tmp = 0;
	unsigned int check;
	u16 adc_gas_res;
	u8 gas_range;

	/* Set heater settings */
	ret = bme680_gas_config(data);
	if (ret < 0) {
		dev_err(dev, "failed to set gas config\n");
		return ret;
	}

	/* set forced mode to trigger measurement */
	ret = bme680_set_mode(data, true);
	if (ret < 0)
		return ret;

	ret = regmap_read(data->regmap, BME680_REG_MEAS_STAT_0, &check);
	if (check & BME680_GAS_MEAS_BIT) {
		dev_err(dev, "gas measurement incomplete\n");
		return -EBUSY;
	}

	ret = regmap_read(data->regmap, BME680_REG_GAS_R_LSB, &check);
	if (ret < 0) {
		dev_err(dev, "failed to read gas_r_lsb register\n");
		return ret;
	}

	/*
	 * occurs if either the gas heating duration was insuffient
	 * to reach the target heater temperature or the target
	 * heater temperature was too high for the heater sink to
	 * reach.
	 */
	if ((check & BME680_GAS_STAB_BIT) == 0) {
		dev_err(dev, "heater failed to reach the target temperature\n");
		return -EINVAL;
	}

	ret = regmap_bulk_read(data->regmap, BME680_REG_GAS_MSB,
			       (u8 *) &tmp, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read gas resistance\n");
		return ret;
	}

	gas_range = check & BME680_GAS_RANGE_MASK;
	adc_gas_res = be16_to_cpu(tmp) >> BME680_ADC_GAS_RES_SHIFT;

	*val = bme680_compensate_gas(data, adc_gas_res, gas_range);
	return IIO_VAL_INT;
}