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
struct regmap_irq_chip {int dummy; } ;
struct regmap_config {int dummy; } ;
struct mfd_cell {int dummy; } ;
struct max77686_dev {unsigned long type; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; struct i2c_client* i2c; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mfd_cell*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX77686_REG_DEVICE_ID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned long TYPE_MAX77686 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct max77686_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct regmap_irq_chip const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max77686_dev*) ; 
 struct mfd_cell* max77686_devs ; 
 struct regmap_irq_chip max77686_irq_chip ; 
 struct regmap_config max77686_regmap_config ; 
 struct mfd_cell* max77802_devs ; 
 struct regmap_irq_chip max77802_irq_chip ; 
 struct regmap_config max77802_regmap_config ; 
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77686_i2c_probe(struct i2c_client *i2c)
{
	struct max77686_dev *max77686 = NULL;
	unsigned int data;
	int ret = 0;
	const struct regmap_config *config;
	const struct regmap_irq_chip *irq_chip;
	const struct mfd_cell *cells;
	int n_devs;

	max77686 = devm_kzalloc(&i2c->dev,
				sizeof(struct max77686_dev), GFP_KERNEL);
	if (!max77686)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max77686);
	max77686->type = (unsigned long)of_device_get_match_data(&i2c->dev);
	max77686->dev = &i2c->dev;
	max77686->i2c = i2c;

	max77686->irq = i2c->irq;

	if (max77686->type == TYPE_MAX77686) {
		config = &max77686_regmap_config;
		irq_chip = &max77686_irq_chip;
		cells =  max77686_devs;
		n_devs = ARRAY_SIZE(max77686_devs);
	} else {
		config = &max77802_regmap_config;
		irq_chip = &max77802_irq_chip;
		cells =  max77802_devs;
		n_devs = ARRAY_SIZE(max77802_devs);
	}

	max77686->regmap = devm_regmap_init_i2c(i2c, config);
	if (IS_ERR(max77686->regmap)) {
		ret = PTR_ERR(max77686->regmap);
		dev_err(max77686->dev, "Failed to allocate register map: %d\n",
				ret);
		return ret;
	}

	ret = regmap_read(max77686->regmap, MAX77686_REG_DEVICE_ID, &data);
	if (ret < 0) {
		dev_err(max77686->dev,
			"device not found on this channel (this is not an error)\n");
		return -ENODEV;
	}

	ret = devm_regmap_add_irq_chip(&i2c->dev, max77686->regmap,
				       max77686->irq,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
				       IRQF_SHARED, 0, irq_chip,
				       &max77686->irq_data);
	if (ret < 0) {
		dev_err(&i2c->dev, "failed to add PMIC irq chip: %d\n", ret);
		return ret;
	}

	ret = devm_mfd_add_devices(max77686->dev, -1, cells, n_devs, NULL,
				   0, NULL);
	if (ret < 0) {
		dev_err(&i2c->dev, "failed to add MFD devices: %d\n", ret);
		return ret;
	}

	return 0;
}