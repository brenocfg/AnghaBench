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
typedef  int u8 ;
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  oversampling_press; int /*<<< orphan*/  oversampling_temp; int /*<<< orphan*/  oversampling_humid; } ;

/* Variables and functions */
 int BME680_FILTER_COEFF_VAL ; 
 int BME680_FILTER_MASK ; 
 int BME680_OSRS_HUMIDITY_MASK ; 
 int BME680_OSRS_PRESS_MASK ; 
 int BME680_OSRS_TEMP_MASK ; 
 int /*<<< orphan*/  BME680_REG_CONFIG ; 
 int /*<<< orphan*/  BME680_REG_CTRL_HUMIDITY ; 
 int /*<<< orphan*/  BME680_REG_CTRL_MEAS ; 
 int FIELD_PREP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bme680_oversampling_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bme680_chip_config(struct bme680_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	u8 osrs;

	osrs = FIELD_PREP(
		BME680_OSRS_HUMIDITY_MASK,
		bme680_oversampling_to_reg(data->oversampling_humid));
	/*
	 * Highly recommended to set oversampling of humidity before
	 * temperature/pressure oversampling.
	 */
	ret = regmap_update_bits(data->regmap, BME680_REG_CTRL_HUMIDITY,
				 BME680_OSRS_HUMIDITY_MASK, osrs);
	if (ret < 0) {
		dev_err(dev, "failed to write ctrl_hum register\n");
		return ret;
	}

	/* IIR filter settings */
	ret = regmap_update_bits(data->regmap, BME680_REG_CONFIG,
				 BME680_FILTER_MASK,
				 BME680_FILTER_COEFF_VAL);
	if (ret < 0) {
		dev_err(dev, "failed to write config register\n");
		return ret;
	}

	osrs = FIELD_PREP(BME680_OSRS_TEMP_MASK,
			  bme680_oversampling_to_reg(data->oversampling_temp)) |
	       FIELD_PREP(BME680_OSRS_PRESS_MASK,
			  bme680_oversampling_to_reg(data->oversampling_press));
	ret = regmap_write_bits(data->regmap, BME680_REG_CTRL_MEAS,
				BME680_OSRS_TEMP_MASK | BME680_OSRS_PRESS_MASK,
				osrs);
	if (ret < 0)
		dev_err(dev, "failed to write ctrl_meas register\n");

	return ret;
}