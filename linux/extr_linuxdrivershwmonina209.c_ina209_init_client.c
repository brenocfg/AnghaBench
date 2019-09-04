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
typedef  int u32 ;
struct ina2xx_platform_data {scalar_t__ shunt_uohms; } ;
struct ina209_data {int calibration_orig; int config_orig; int /*<<< orphan*/  update_interval; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INA209_CALIBRATION ; 
 int /*<<< orphan*/  INA209_CONFIGURATION ; 
 int /*<<< orphan*/  INA209_CONFIG_DEFAULT ; 
 int INA209_SHUNT_DEFAULT ; 
 int /*<<< orphan*/  INA209_STATUS ; 
 int /*<<< orphan*/  clamp_val (int,int,int) ; 
 struct ina2xx_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ina209_interval_from_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int ina209_init_client(struct i2c_client *client,
			      struct ina209_data *data)
{
	struct ina2xx_platform_data *pdata = dev_get_platdata(&client->dev);
	u32 shunt;
	int reg;

	reg = i2c_smbus_read_word_swapped(client, INA209_CALIBRATION);
	if (reg < 0)
		return reg;
	data->calibration_orig = reg;

	reg = i2c_smbus_read_word_swapped(client, INA209_CONFIGURATION);
	if (reg < 0)
		return reg;
	data->config_orig = reg;

	if (pdata) {
		if (pdata->shunt_uohms <= 0)
			return -EINVAL;
		shunt = pdata->shunt_uohms;
	} else if (!of_property_read_u32(client->dev.of_node, "shunt-resistor",
					 &shunt)) {
		if (shunt == 0)
			return -EINVAL;
	} else {
		shunt = data->calibration_orig ?
		  40960000 / data->calibration_orig : INA209_SHUNT_DEFAULT;
	}

	i2c_smbus_write_word_swapped(client, INA209_CONFIGURATION,
				     INA209_CONFIG_DEFAULT);
	data->update_interval = ina209_interval_from_reg(INA209_CONFIG_DEFAULT);

	/*
	 * Calibrate current LSB to 1mA. Shunt is in uOhms.
	 * See equation 13 in datasheet.
	 */
	i2c_smbus_write_word_swapped(client, INA209_CALIBRATION,
				     clamp_val(40960000 / shunt, 1, 65535));

	/* Clear status register */
	i2c_smbus_read_word_swapped(client, INA209_STATUS);

	return 0;
}