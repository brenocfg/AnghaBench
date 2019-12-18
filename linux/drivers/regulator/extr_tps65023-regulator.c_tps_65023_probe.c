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
struct tps_pmic {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * rdev; struct tps_driver_data* driver_data; } ;
struct tps_driver_data {int /*<<< orphan*/ * desc; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_config {struct regulator_init_data* init_data; int /*<<< orphan*/  regmap; struct tps_pmic* driver_data; int /*<<< orphan*/ * dev; } ;
struct i2c_device_id {int name; scalar_t__ driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TPS65023_NUM_REGULATOR ; 
 int /*<<< orphan*/  TPS65023_REG_CON_CTRL2 ; 
 int /*<<< orphan*/  TPS65023_REG_CTRL2_CORE_ADJ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regulator_init_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct tps_pmic* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps_pmic*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps65023_regmap_config ; 

__attribute__((used)) static int tps_65023_probe(struct i2c_client *client,
				     const struct i2c_device_id *id)
{
	struct regulator_init_data *init_data = dev_get_platdata(&client->dev);
	struct regulator_config config = { };
	struct tps_pmic *tps;
	int i;
	int error;

	tps = devm_kzalloc(&client->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	tps->driver_data = (struct tps_driver_data *)id->driver_data;

	tps->regmap = devm_regmap_init_i2c(client, &tps65023_regmap_config);
	if (IS_ERR(tps->regmap)) {
		error = PTR_ERR(tps->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			error);
		return error;
	}

	/* common for all regulators */
	config.dev = &client->dev;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	for (i = 0; i < TPS65023_NUM_REGULATOR; i++) {
		if (init_data)
			config.init_data = &init_data[i];

		/* Register the regulators */
		tps->rdev[i] = devm_regulator_register(&client->dev,
					&tps->driver_data->desc[i], &config);
		if (IS_ERR(tps->rdev[i])) {
			dev_err(&client->dev, "failed to register %s\n",
				id->name);
			return PTR_ERR(tps->rdev[i]);
		}
	}

	i2c_set_clientdata(client, tps);

	/* Enable setting output voltage by I2C */
	regmap_update_bits(tps->regmap, TPS65023_REG_CON_CTRL2,
			   TPS65023_REG_CTRL2_CORE_ADJ, 0);

	return 0;
}