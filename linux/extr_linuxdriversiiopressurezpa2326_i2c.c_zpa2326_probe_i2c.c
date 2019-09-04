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
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpa2326_i2c_hwid (struct i2c_client*) ; 
 int zpa2326_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regmap*) ; 
 int /*<<< orphan*/  zpa2326_regmap_i2c_config ; 

__attribute__((used)) static int zpa2326_probe_i2c(struct i2c_client          *client,
			     const struct i2c_device_id *i2c_id)
{
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &zpa2326_regmap_i2c_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "failed to init registers map");
		return PTR_ERR(regmap);
	}

	return zpa2326_probe(&client->dev, i2c_id->name, client->irq,
			     zpa2326_i2c_hwid(client), regmap);
}