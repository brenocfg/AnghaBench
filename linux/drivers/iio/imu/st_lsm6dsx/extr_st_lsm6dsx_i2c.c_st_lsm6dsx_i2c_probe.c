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
struct i2c_device_id {int driver_data; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_lsm6dsx_i2c_regmap_config ; 
 int st_lsm6dsx_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct regmap*) ; 

__attribute__((used)) static int st_lsm6dsx_i2c_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	int hw_id = id->driver_data;
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &st_lsm6dsx_i2c_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Failed to register i2c regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return st_lsm6dsx_probe(&client->dev, client->irq, hw_id, regmap);
}