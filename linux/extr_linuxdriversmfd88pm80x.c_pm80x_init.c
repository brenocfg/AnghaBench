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
struct regmap {int dummy; } ;
struct pm80x_chip {struct i2c_client* client; struct i2c_client* companion; int /*<<< orphan*/ * dev; int /*<<< orphan*/  type; struct regmap* regmap; int /*<<< orphan*/  irq; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  PM80X_CHIP_ID ; 
 scalar_t__ PM80X_CHIP_ID_NUM (unsigned int) ; 
 int PTR_ERR (struct regmap*) ; 
 TYPE_1__* chip_mapping ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct pm80x_chip*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct pm80x_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct pm80x_chip* g_pm80x_chip ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pm80x_chip*) ; 
 int /*<<< orphan*/  pm80x_regmap_config ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

int pm80x_init(struct i2c_client *client)
{
	struct pm80x_chip *chip;
	struct regmap *map;
	unsigned int val;
	int i, ret = 0;

	chip =
	    devm_kzalloc(&client->dev, sizeof(struct pm80x_chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	map = devm_regmap_init_i2c(client, &pm80x_regmap_config);
	if (IS_ERR(map)) {
		ret = PTR_ERR(map);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	chip->client = client;
	chip->regmap = map;

	chip->irq = client->irq;

	chip->dev = &client->dev;
	dev_set_drvdata(chip->dev, chip);
	i2c_set_clientdata(chip->client, chip);

	ret = regmap_read(chip->regmap, PM80X_CHIP_ID, &val);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read CHIP ID: %d\n", ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(chip_mapping); i++) {
		if (chip_mapping[i].id == PM80X_CHIP_ID_NUM(val)) {
			chip->type = chip_mapping[i].type;
			break;
		}
	}

	if (i == ARRAY_SIZE(chip_mapping)) {
		dev_err(chip->dev,
			"Failed to detect Marvell 88PM800:ChipID[0x%x]\n", val);
		return -EINVAL;
	}

	device_init_wakeup(&client->dev, 1);

	/*
	 * workaround: set g_pm80x_chip to the first probed chip. if the
	 * second chip is probed, just point to the companion to each
	 * other so that pm805 can access those specific register. would
	 * remove it after HW chip fixes the issue.
	 */
	if (!g_pm80x_chip)
		g_pm80x_chip = chip;
	else {
		chip->companion = g_pm80x_chip->client;
		g_pm80x_chip->companion = chip->client;
	}

	return 0;
}