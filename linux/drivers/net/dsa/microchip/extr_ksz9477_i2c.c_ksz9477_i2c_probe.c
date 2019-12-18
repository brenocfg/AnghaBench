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
struct regmap_config {int /*<<< orphan*/  val_bits; int /*<<< orphan*/ * lock_arg; } ;
struct ksz_device {scalar_t__ pdata; int /*<<< orphan*/ * regmap; int /*<<< orphan*/  regmap_mutex; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {scalar_t__ platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct regmap_config*) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ksz_device*) ; 
 struct regmap_config* ksz9477_regmap_config ; 
 int ksz9477_switch_register (struct ksz_device*) ; 
 struct ksz_device* ksz_switch_alloc (TYPE_1__*,struct i2c_client*) ; 

__attribute__((used)) static int ksz9477_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *i2c_id)
{
	struct regmap_config rc;
	struct ksz_device *dev;
	int i, ret;

	dev = ksz_switch_alloc(&i2c->dev, i2c);
	if (!dev)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(ksz9477_regmap_config); i++) {
		rc = ksz9477_regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init_i2c(i2c, &rc);
		if (IS_ERR(dev->regmap[i])) {
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&i2c->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz9477_regmap_config[i].val_bits, ret);
			return ret;
		}
	}

	if (i2c->dev.platform_data)
		dev->pdata = i2c->dev.platform_data;

	ret = ksz9477_switch_register(dev);

	/* Main DSA driver may not be started yet. */
	if (ret)
		return ret;

	i2c_set_clientdata(i2c, dev);

	return 0;
}