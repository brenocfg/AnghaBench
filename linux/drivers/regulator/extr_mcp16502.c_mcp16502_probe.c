#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {struct mcp16502* driver_data; struct regulator_dev* regmap; struct device* dev; } ;
typedef  struct regulator_dev regmap ;
struct mcp16502 {struct regulator_dev* lpm; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  MCP16502_OPMODE_ACTIVE ; 
 int NUM_REGULATORS ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct regulator_dev* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mcp16502* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (struct device*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mcp16502*) ; 
 TYPE_1__* mcp16502_desc ; 
 int /*<<< orphan*/  mcp16502_gpio_set_mode (struct mcp16502*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp16502_regmap_config ; 

__attribute__((used)) static int mcp16502_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	struct device *dev;
	struct mcp16502 *mcp;
	struct regmap *rmap;
	int i, ret;

	dev = &client->dev;
	config.dev = dev;

	mcp = devm_kzalloc(dev, sizeof(*mcp), GFP_KERNEL);
	if (!mcp)
		return -ENOMEM;

	rmap = devm_regmap_init_i2c(client, &mcp16502_regmap_config);
	if (IS_ERR(rmap)) {
		ret = PTR_ERR(rmap);
		dev_err(dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, mcp);
	config.regmap = rmap;
	config.driver_data = mcp;

	mcp->lpm = devm_gpiod_get(dev, "lpm", GPIOD_OUT_LOW);
	if (IS_ERR(mcp->lpm)) {
		dev_err(dev, "failed to get lpm pin: %ld\n", PTR_ERR(mcp->lpm));
		return PTR_ERR(mcp->lpm);
	}

	for (i = 0; i < NUM_REGULATORS; i++) {
		rdev = devm_regulator_register(dev, &mcp16502_desc[i], &config);
		if (IS_ERR(rdev)) {
			dev_err(dev,
				"failed to register %s regulator %ld\n",
				mcp16502_desc[i].name, PTR_ERR(rdev));
			return PTR_ERR(rdev);
		}
	}

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_ACTIVE);

	return 0;
}