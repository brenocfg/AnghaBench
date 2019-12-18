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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct da9055 {int /*<<< orphan*/  chip_irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int da9055_device_init (struct da9055*) ; 
 int /*<<< orphan*/  da9055_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct da9055* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da9055*) ; 

__attribute__((used)) static int da9055_i2c_probe(struct i2c_client *i2c,
				      const struct i2c_device_id *id)
{
	struct da9055 *da9055;
	int ret;

	da9055 = devm_kzalloc(&i2c->dev, sizeof(struct da9055), GFP_KERNEL);
	if (!da9055)
		return -ENOMEM;

	da9055->regmap = devm_regmap_init_i2c(i2c, &da9055_regmap_config);
	if (IS_ERR(da9055->regmap)) {
		ret = PTR_ERR(da9055->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	da9055->dev = &i2c->dev;
	da9055->chip_irq = i2c->irq;

	i2c_set_clientdata(i2c, da9055);

	return da9055_device_init(da9055);
}