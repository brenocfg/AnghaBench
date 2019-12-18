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
typedef  int u32 ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  init_data; int /*<<< orphan*/  of_node; struct regulator_dev* regmap; struct device* dev; } ;
typedef  struct regulator_dev regmap ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 unsigned int SY8106A_GO_BIT ; 
 int SY8106A_MAX_MV ; 
 int SY8106A_MIN_MV ; 
 int /*<<< orphan*/  SY8106A_REG_VOUT1_SEL ; 
 int SY8106A_STEP_MV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (struct device*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int regmap_read (struct regulator_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regulator_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sy8106a_reg ; 
 int /*<<< orphan*/  sy8106a_regmap_config ; 

__attribute__((used)) static int sy8106a_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct regulator_dev *rdev;
	struct regulator_config config = { };
	struct regmap *regmap;
	unsigned int reg, vsel;
	u32 fixed_voltage;
	int error;

	error = of_property_read_u32(dev->of_node, "silergy,fixed-microvolt",
				     &fixed_voltage);
	if (error)
		return error;

	if (fixed_voltage < SY8106A_MIN_MV * 1000 ||
	    fixed_voltage > SY8106A_MAX_MV * 1000)
		return -EINVAL;

	regmap = devm_regmap_init_i2c(i2c, &sy8106a_regmap_config);
	if (IS_ERR(regmap)) {
		error = PTR_ERR(regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		return error;
	}

	config.dev = &i2c->dev;
	config.regmap = regmap;

	config.of_node = dev->of_node;
	config.init_data = of_get_regulator_init_data(dev, dev->of_node,
						      &sy8106a_reg);

	if (!config.init_data)
		return -ENOMEM;

	/* Ensure GO_BIT is enabled when probing */
	error = regmap_read(regmap, SY8106A_REG_VOUT1_SEL, &reg);
	if (error)
		return error;

	if (!(reg & SY8106A_GO_BIT)) {
		vsel = (fixed_voltage / 1000 - SY8106A_MIN_MV) /
		       SY8106A_STEP_MV;

		error = regmap_write(regmap, SY8106A_REG_VOUT1_SEL,
				     vsel | SY8106A_GO_BIT);
		if (error)
			return error;
	}

	/* Probe regulator */
	rdev = devm_regulator_register(&i2c->dev, &sy8106a_reg, &config);
	if (IS_ERR(rdev)) {
		error = PTR_ERR(rdev);
		dev_err(&i2c->dev, "Failed to register SY8106A regulator: %d\n", error);
		return error;
	}

	return 0;
}