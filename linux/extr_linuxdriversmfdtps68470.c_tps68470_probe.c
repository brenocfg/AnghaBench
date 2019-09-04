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
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct regmap*) ; 
 int tps68470_chip_init (struct device*,struct regmap*) ; 
 int /*<<< orphan*/  tps68470_regmap_config ; 
 int /*<<< orphan*/  tps68470s ; 

__attribute__((used)) static int tps68470_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_i2c(client, &tps68470_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(dev, "devm_regmap_init_i2c Error %ld\n",
			PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	i2c_set_clientdata(client, regmap);

	ret = tps68470_chip_init(dev, regmap);
	if (ret < 0) {
		dev_err(dev, "TPS68470 Init Error %d\n", ret);
		return ret;
	}

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE, tps68470s,
			      ARRAY_SIZE(tps68470s), NULL, 0, NULL);
	if (ret < 0) {
		dev_err(dev, "devm_mfd_add_devices failed: %d\n", ret);
		return ret;
	}

	return 0;
}