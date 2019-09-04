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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  act8945a_devs ; 
 int /*<<< orphan*/  act8945a_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct regmap*) ; 

__attribute__((used)) static int act8945a_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	int ret;
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &act8945a_regmap_config);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, regmap);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_NONE,
				   act8945a_devs, ARRAY_SIZE(act8945a_devs),
				   NULL, 0, NULL);
	if (ret) {
		dev_err(&i2c->dev, "Failed to add sub devices\n");
		return ret;
	}

	return 0;
}