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
struct rt5033_dev {int wakeup; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5033_REG_DEVICE_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct rt5033_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5033_dev*) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rt5033_devs ; 
 int /*<<< orphan*/  rt5033_irq_chip ; 
 int /*<<< orphan*/  rt5033_regmap_config ; 

__attribute__((used)) static int rt5033_i2c_probe(struct i2c_client *i2c,
				const struct i2c_device_id *id)
{
	struct rt5033_dev *rt5033;
	unsigned int dev_id;
	int ret;

	rt5033 = devm_kzalloc(&i2c->dev, sizeof(*rt5033), GFP_KERNEL);
	if (!rt5033)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5033);
	rt5033->dev = &i2c->dev;
	rt5033->irq = i2c->irq;
	rt5033->wakeup = true;

	rt5033->regmap = devm_regmap_init_i2c(i2c, &rt5033_regmap_config);
	if (IS_ERR(rt5033->regmap)) {
		dev_err(&i2c->dev, "Failed to allocate register map.\n");
		return PTR_ERR(rt5033->regmap);
	}

	ret = regmap_read(rt5033->regmap, RT5033_REG_DEVICE_ID, &dev_id);
	if (ret) {
		dev_err(&i2c->dev, "Device not found\n");
		return -ENODEV;
	}
	dev_info(&i2c->dev, "Device found Device ID: %04x\n", dev_id);

	ret = regmap_add_irq_chip(rt5033->regmap, rt5033->irq,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			0, &rt5033_irq_chip, &rt5033->irq_data);
	if (ret) {
		dev_err(&i2c->dev, "Failed to request IRQ %d: %d\n",
							rt5033->irq, ret);
		return ret;
	}

	ret = devm_mfd_add_devices(rt5033->dev, -1, rt5033_devs,
				   ARRAY_SIZE(rt5033_devs), NULL, 0,
				   regmap_irq_get_domain(rt5033->irq_data));
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to add RT5033 child devices.\n");
		return ret;
	}

	device_init_wakeup(rt5033->dev, rt5033->wakeup);

	return 0;
}