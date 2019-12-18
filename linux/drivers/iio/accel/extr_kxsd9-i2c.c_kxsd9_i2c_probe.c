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
struct regmap_config {int reg_bits; int val_bits; int max_register; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int kxsd9_common_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kxsd9_i2c_probe(struct i2c_client *i2c,
			   const struct i2c_device_id *id)
{
	static const struct regmap_config config = {
		.reg_bits = 8,
		.val_bits = 8,
		.max_register = 0x0e,
	};
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &config);
	if (IS_ERR(regmap)) {
		dev_err(&i2c->dev, "Failed to register i2c regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return kxsd9_common_probe(&i2c->dev,
				  regmap,
				  i2c->name);
}