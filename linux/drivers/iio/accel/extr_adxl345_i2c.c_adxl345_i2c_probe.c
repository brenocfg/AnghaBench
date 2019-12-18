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
struct i2c_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int adxl345_core_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adxl345_i2c_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adxl345_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;

	if (!id)
		return -ENODEV;

	regmap = devm_regmap_init_i2c(client, &adxl345_i2c_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Error initializing i2c regmap: %ld\n",
			PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return adxl345_core_probe(&client->dev, regmap, id->driver_data,
				  id->name);
}