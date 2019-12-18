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
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  heater_dur; int /*<<< orphan*/  heater_temp; } ;

/* Variables and functions */
 int BME680_NB_CONV_MASK ; 
 int /*<<< orphan*/  BME680_REG_CTRL_GAS_1 ; 
 int /*<<< orphan*/  BME680_REG_GAS_WAIT_0 ; 
 int /*<<< orphan*/  BME680_REG_RES_HEAT_0 ; 
 int BME680_RUN_GAS_MASK ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  bme680_calc_heater_dur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bme680_calc_heater_res (struct bme680_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme680_gas_config(struct bme680_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	u8 heatr_res, heatr_dur;

	heatr_res = bme680_calc_heater_res(data, data->heater_temp);

	/* set target heater temperature */
	ret = regmap_write(data->regmap, BME680_REG_RES_HEAT_0, heatr_res);
	if (ret < 0) {
		dev_err(dev, "failed to write res_heat_0 register\n");
		return ret;
	}

	heatr_dur = bme680_calc_heater_dur(data->heater_dur);

	/* set target heating duration */
	ret = regmap_write(data->regmap, BME680_REG_GAS_WAIT_0, heatr_dur);
	if (ret < 0) {
		dev_err(dev, "failed to write gas_wait_0 register\n");
		return ret;
	}

	/* Enable the gas sensor and select heater profile set-point 0 */
	ret = regmap_update_bits(data->regmap, BME680_REG_CTRL_GAS_1,
				 BME680_RUN_GAS_MASK | BME680_NB_CONV_MASK,
				 FIELD_PREP(BME680_RUN_GAS_MASK, 1) |
				 FIELD_PREP(BME680_NB_CONV_MASK, 0));
	if (ret < 0)
		dev_err(dev, "failed to write ctrl_gas_1 register\n");

	return ret;
}