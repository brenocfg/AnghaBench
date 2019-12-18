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
struct power_supply_config {struct adp5061_state* drv_data; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adp5061_state {int /*<<< orphan*/  psy; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp5061_desc ; 
 int /*<<< orphan*/  adp5061_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adp5061_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adp5061_state*) ; 

__attribute__((used)) static int adp5061_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct power_supply_config psy_cfg = {};
	struct adp5061_state *st;

	st = devm_kzalloc(&client->dev, sizeof(*st), GFP_KERNEL);
	if (!st)
		return -ENOMEM;

	st->client = client;
	st->regmap = devm_regmap_init_i2c(client,
					  &adp5061_regmap_config);
	if (IS_ERR(st->regmap)) {
		dev_err(&client->dev, "Failed to initialize register map\n");
		return -EINVAL;
	}

	i2c_set_clientdata(client, st);
	psy_cfg.drv_data = st;

	st->psy = devm_power_supply_register(&client->dev,
					     &adp5061_desc,
					     &psy_cfg);

	if (IS_ERR(st->psy)) {
		dev_err(&client->dev, "Failed to register power supply\n");
		return PTR_ERR(st->psy);
	}

	return 0;
}