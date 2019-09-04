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
struct regulator {int dummy; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct ads7828_platform_data {int diff_input; int ext_vref; unsigned int vref_mv; } ;
struct ads7828_data {int /*<<< orphan*/  cmd_byte; struct regulator* regmap; void* lsb_resol; } ;
typedef  enum ads7828_chips { ____Placeholder_ads7828_chips } ads7828_chips ;

/* Variables and functions */
 int /*<<< orphan*/  ADS7828_CMD_PD1 ; 
 int /*<<< orphan*/  ADS7828_CMD_PD3 ; 
 int /*<<< orphan*/  ADS7828_CMD_SD_SE ; 
 unsigned int ADS7828_EXT_VREF_MV_MAX ; 
 unsigned int ADS7828_EXT_VREF_MV_MIN ; 
 unsigned int ADS7828_INT_VREF_MV ; 
 void* DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  ads2828_regmap_config ; 
 int /*<<< orphan*/  ads2830_regmap_config ; 
 int ads7828 ; 
 int /*<<< orphan*/  ads7828_groups ; 
 unsigned int clamp_val (unsigned int,unsigned int,unsigned int) ; 
 struct ads7828_platform_data* dev_get_platdata (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct ads7828_data*,int /*<<< orphan*/ ) ; 
 struct ads7828_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator* devm_regulator_get_optional (struct device*,char*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int of_property_read_bool (scalar_t__,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regulator*,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int regulator_get_voltage (struct regulator*) ; 

__attribute__((used)) static int ads7828_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ads7828_platform_data *pdata = dev_get_platdata(dev);
	struct ads7828_data *data;
	struct device *hwmon_dev;
	unsigned int vref_mv = ADS7828_INT_VREF_MV;
	unsigned int vref_uv;
	bool diff_input = false;
	bool ext_vref = false;
	unsigned int regval;
	enum ads7828_chips chip;
	struct regulator *reg;

	data = devm_kzalloc(dev, sizeof(struct ads7828_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	if (pdata) {
		diff_input = pdata->diff_input;
		ext_vref = pdata->ext_vref;
		if (ext_vref && pdata->vref_mv)
			vref_mv = pdata->vref_mv;
	} else if (dev->of_node) {
		diff_input = of_property_read_bool(dev->of_node,
						   "ti,differential-input");
		reg = devm_regulator_get_optional(dev, "vref");
		if (!IS_ERR(reg)) {
			vref_uv = regulator_get_voltage(reg);
			vref_mv = DIV_ROUND_CLOSEST(vref_uv, 1000);
			if (vref_mv < ADS7828_EXT_VREF_MV_MIN ||
			    vref_mv > ADS7828_EXT_VREF_MV_MAX)
				return -EINVAL;
			ext_vref = true;
		}
	}

	if (client->dev.of_node)
		chip = (enum ads7828_chips)
			of_device_get_match_data(&client->dev);
	else
		chip = id->driver_data;

	/* Bound Vref with min/max values */
	vref_mv = clamp_val(vref_mv, ADS7828_EXT_VREF_MV_MIN,
			    ADS7828_EXT_VREF_MV_MAX);

	/* ADS7828 uses 12-bit samples, while ADS7830 is 8-bit */
	if (chip == ads7828) {
		data->lsb_resol = DIV_ROUND_CLOSEST(vref_mv * 1000, 4096);
		data->regmap = devm_regmap_init_i2c(client,
						    &ads2828_regmap_config);
	} else {
		data->lsb_resol = DIV_ROUND_CLOSEST(vref_mv * 1000, 256);
		data->regmap = devm_regmap_init_i2c(client,
						    &ads2830_regmap_config);
	}

	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	data->cmd_byte = ext_vref ? ADS7828_CMD_PD1 : ADS7828_CMD_PD3;
	if (!diff_input)
		data->cmd_byte |= ADS7828_CMD_SD_SE;

	/*
	 * Datasheet specifies internal reference voltage is disabled by
	 * default. The internal reference voltage needs to be enabled and
	 * voltage needs to settle before getting valid ADC data. So perform a
	 * dummy read to enable the internal reference voltage.
	 */
	if (!ext_vref)
		regmap_read(data->regmap, data->cmd_byte, &regval);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   ads7828_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}