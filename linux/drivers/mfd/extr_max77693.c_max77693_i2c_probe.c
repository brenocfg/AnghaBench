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
struct max77693_dev {struct i2c_client* i2c_muic; struct i2c_client* i2c_haptic; int /*<<< orphan*/  irq_data_led; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_data_topsys; int /*<<< orphan*/  irq_data_chg; int /*<<< orphan*/  irq_data_muic; int /*<<< orphan*/ * dev; struct i2c_client* regmap; struct i2c_client* regmap_muic; struct i2c_client* regmap_haptic; int /*<<< orphan*/  type; struct i2c_client* i2c; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_ADDR_HAPTIC ; 
 int /*<<< orphan*/  I2C_ADDR_MUIC ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  MAX77693_PMIC_REG_INTSRC_MASK ; 
 int /*<<< orphan*/  MAX77693_PMIC_REG_PMIC_ID2 ; 
 int PTR_ERR (struct i2c_client*) ; 
 scalar_t__ SRC_IRQ_ALL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct max77693_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 void* i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max77693_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  max77693_charger_irq_chip ; 
 int /*<<< orphan*/  max77693_devs ; 
 int /*<<< orphan*/  max77693_led_irq_chip ; 
 int /*<<< orphan*/  max77693_muic_irq_chip ; 
 int /*<<< orphan*/  max77693_regmap_config ; 
 int /*<<< orphan*/  max77693_regmap_haptic_config ; 
 int /*<<< orphan*/  max77693_regmap_muic_config ; 
 int /*<<< orphan*/  max77693_topsys_irq_chip ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int regmap_add_irq_chip (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (struct i2c_client*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int max77693_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct max77693_dev *max77693;
	unsigned int reg_data;
	int ret = 0;

	max77693 = devm_kzalloc(&i2c->dev,
			sizeof(struct max77693_dev), GFP_KERNEL);
	if (max77693 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max77693);
	max77693->dev = &i2c->dev;
	max77693->i2c = i2c;
	max77693->irq = i2c->irq;
	max77693->type = id->driver_data;

	max77693->regmap = devm_regmap_init_i2c(i2c, &max77693_regmap_config);
	if (IS_ERR(max77693->regmap)) {
		ret = PTR_ERR(max77693->regmap);
		dev_err(max77693->dev, "failed to allocate register map: %d\n",
				ret);
		return ret;
	}

	ret = regmap_read(max77693->regmap, MAX77693_PMIC_REG_PMIC_ID2,
				&reg_data);
	if (ret < 0) {
		dev_err(max77693->dev, "device not found on this channel\n");
		return ret;
	} else
		dev_info(max77693->dev, "device ID: 0x%x\n", reg_data);

	max77693->i2c_muic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_MUIC);
	if (IS_ERR(max77693->i2c_muic)) {
		dev_err(max77693->dev, "Failed to allocate I2C device for MUIC\n");
		return PTR_ERR(max77693->i2c_muic);
	}
	i2c_set_clientdata(max77693->i2c_muic, max77693);

	max77693->i2c_haptic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_HAPTIC);
	if (IS_ERR(max77693->i2c_haptic)) {
		dev_err(max77693->dev, "Failed to allocate I2C device for Haptic\n");
		ret = PTR_ERR(max77693->i2c_haptic);
		goto err_i2c_haptic;
	}
	i2c_set_clientdata(max77693->i2c_haptic, max77693);

	max77693->regmap_haptic = devm_regmap_init_i2c(max77693->i2c_haptic,
					&max77693_regmap_haptic_config);
	if (IS_ERR(max77693->regmap_haptic)) {
		ret = PTR_ERR(max77693->regmap_haptic);
		dev_err(max77693->dev,
			"failed to initialize haptic register map: %d\n", ret);
		goto err_regmap;
	}

	/*
	 * Initialize register map for MUIC device because use regmap-muic
	 * instance of MUIC device when irq of max77693 is initialized
	 * before call max77693-muic probe() function.
	 */
	max77693->regmap_muic = devm_regmap_init_i2c(max77693->i2c_muic,
					 &max77693_regmap_muic_config);
	if (IS_ERR(max77693->regmap_muic)) {
		ret = PTR_ERR(max77693->regmap_muic);
		dev_err(max77693->dev,
			"failed to allocate register map: %d\n", ret);
		goto err_regmap;
	}

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_led_irq_chip,
				&max77693->irq_data_led);
	if (ret) {
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		goto err_regmap;
	}

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_topsys_irq_chip,
				&max77693->irq_data_topsys);
	if (ret) {
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		goto err_irq_topsys;
	}

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_charger_irq_chip,
				&max77693->irq_data_chg);
	if (ret) {
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		goto err_irq_charger;
	}

	ret = regmap_add_irq_chip(max77693->regmap_muic, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_muic_irq_chip,
				&max77693->irq_data_muic);
	if (ret) {
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		goto err_irq_muic;
	}

	/* Unmask interrupts from all blocks in interrupt source register */
	ret = regmap_update_bits(max77693->regmap,
				MAX77693_PMIC_REG_INTSRC_MASK,
				SRC_IRQ_ALL, (unsigned int)~SRC_IRQ_ALL);
	if (ret < 0) {
		dev_err(max77693->dev,
			"Could not unmask interrupts in INTSRC: %d\n",
			ret);
		goto err_intsrc;
	}

	pm_runtime_set_active(max77693->dev);

	ret = mfd_add_devices(max77693->dev, -1, max77693_devs,
			      ARRAY_SIZE(max77693_devs), NULL, 0, NULL);
	if (ret < 0)
		goto err_mfd;

	return ret;

err_mfd:
	mfd_remove_devices(max77693->dev);
err_intsrc:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_muic);
err_irq_muic:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_chg);
err_irq_charger:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_topsys);
err_irq_topsys:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_led);
err_regmap:
	i2c_unregister_device(max77693->i2c_haptic);
err_i2c_haptic:
	i2c_unregister_device(max77693->i2c_muic);
	return ret;
}