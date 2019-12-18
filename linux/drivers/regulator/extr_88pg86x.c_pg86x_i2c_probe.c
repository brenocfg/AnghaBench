#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/ * dev; } ;
typedef  struct regulator_dev regmap ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ *,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  pg86x_regmap ; 
 TYPE_1__* pg86x_regulators ; 

__attribute__((used)) static int pg86x_i2c_probe(struct i2c_client *i2c)
{
	int id, ret;
	struct regulator_config config = {.dev = &i2c->dev};
	struct regmap *regmap = devm_regmap_init_i2c(i2c, &pg86x_regmap);

	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	for (id = 0; id < ARRAY_SIZE(pg86x_regulators); id++) {
		struct regulator_dev *rdev;
		rdev = devm_regulator_register(&i2c->dev,
					       &pg86x_regulators[id],
					       &config);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(&i2c->dev, "failed to register %s: %d\n",
				pg86x_regulators[id].name, ret);
			return ret;
		}
	}
	return 0;
}