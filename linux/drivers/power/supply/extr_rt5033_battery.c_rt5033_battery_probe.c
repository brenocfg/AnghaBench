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
struct rt5033_battery {int /*<<< orphan*/  psy; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct power_supply_config {struct rt5033_battery* drv_data; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rt5033_battery* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5033_battery*) ; 
 int /*<<< orphan*/  power_supply_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  rt5033_battery_desc ; 
 int /*<<< orphan*/  rt5033_battery_regmap_config ; 

__attribute__((used)) static int rt5033_battery_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct power_supply_config psy_cfg = {};
	struct rt5033_battery *battery;
	u32 ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		return -EIO;

	battery = devm_kzalloc(&client->dev, sizeof(*battery), GFP_KERNEL);
	if (!battery)
		return -EINVAL;

	battery->client = client;
	battery->regmap = devm_regmap_init_i2c(client,
			&rt5033_battery_regmap_config);
	if (IS_ERR(battery->regmap)) {
		dev_err(&client->dev, "Failed to initialize regmap\n");
		return -EINVAL;
	}

	i2c_set_clientdata(client, battery);
	psy_cfg.drv_data = battery;

	battery->psy = power_supply_register(&client->dev,
					     &rt5033_battery_desc, &psy_cfg);
	if (IS_ERR(battery->psy)) {
		dev_err(&client->dev, "Failed to register power supply\n");
		ret = PTR_ERR(battery->psy);
		return ret;
	}

	return 0;
}