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
struct regmap {int dummy; } ;
struct i2c_device_id {char* name; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int bmc150_magn_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bmc150_magn_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_magn_i2c_probe(struct i2c_client *client,
				 const struct i2c_device_id *id)
{
	struct regmap *regmap;
	const char *name = NULL;

	regmap = devm_regmap_init_i2c(client, &bmc150_magn_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Failed to initialize i2c regmap\n");
		return PTR_ERR(regmap);
	}

	if (id)
		name = id->name;

	return bmc150_magn_probe(&client->dev, regmap, client->irq, name);
}