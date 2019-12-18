#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct TYPE_3__ {unsigned int chip_type; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;
struct bd718xx {int /*<<< orphan*/  irq_data; TYPE_1__ chip; scalar_t__ chip_irq; } ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BD718XX_INT_PWRBTN_S ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int bd718xx_init_press_duration (struct bd718xx*) ; 
 int /*<<< orphan*/  bd718xx_irq_chip ; 
 int /*<<< orphan*/  bd718xx_mfd_cells ; 
 int /*<<< orphan*/  bd718xx_regmap_config ; 
 TYPE_2__ button ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct bd718xx*) ; 
 struct bd718xx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bd718xx_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct bd718xx *bd718xx;
	int ret;

	if (!i2c->irq) {
		dev_err(&i2c->dev, "No IRQ configured\n");
		return -EINVAL;
	}

	bd718xx = devm_kzalloc(&i2c->dev, sizeof(struct bd718xx), GFP_KERNEL);

	if (!bd718xx)
		return -ENOMEM;

	bd718xx->chip_irq = i2c->irq;
	bd718xx->chip.chip_type = (unsigned int)(uintptr_t)
				of_device_get_match_data(&i2c->dev);
	bd718xx->chip.dev = &i2c->dev;
	dev_set_drvdata(&i2c->dev, bd718xx);

	bd718xx->chip.regmap = devm_regmap_init_i2c(i2c,
						    &bd718xx_regmap_config);
	if (IS_ERR(bd718xx->chip.regmap)) {
		dev_err(&i2c->dev, "regmap initialization failed\n");
		return PTR_ERR(bd718xx->chip.regmap);
	}

	ret = devm_regmap_add_irq_chip(&i2c->dev, bd718xx->chip.regmap,
				       bd718xx->chip_irq, IRQF_ONESHOT, 0,
				       &bd718xx_irq_chip, &bd718xx->irq_data);
	if (ret) {
		dev_err(&i2c->dev, "Failed to add irq_chip\n");
		return ret;
	}

	ret = bd718xx_init_press_duration(bd718xx);
	if (ret)
		return ret;

	ret = regmap_irq_get_virq(bd718xx->irq_data, BD718XX_INT_PWRBTN_S);

	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to get the IRQ\n");
		return ret;
	}

	button.irq = ret;

	ret = devm_mfd_add_devices(bd718xx->chip.dev, PLATFORM_DEVID_AUTO,
				   bd718xx_mfd_cells,
				   ARRAY_SIZE(bd718xx_mfd_cells), NULL, 0,
				   regmap_irq_get_domain(bd718xx->irq_data));
	if (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	return ret;
}