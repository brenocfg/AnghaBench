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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  LTC2945_FAULT ; 
 int PTR_ERR (struct regmap*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct regmap*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltc2945_groups ; 
 int /*<<< orphan*/  ltc2945_regmap_config ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ltc2945_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &ltc2945_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to allocate register map\n");
		return PTR_ERR(regmap);
	}

	/* Clear faults */
	regmap_write(regmap, LTC2945_FAULT, 0x00);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   regmap,
							   ltc2945_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}