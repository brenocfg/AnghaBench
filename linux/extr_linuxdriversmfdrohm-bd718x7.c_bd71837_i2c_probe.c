#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct bd71837 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  chip_irq; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  BD71837_INT_PWRBTN_S ; 
 int /*<<< orphan*/  BD71837_REG_PWRONCONFIG0 ; 
 int /*<<< orphan*/  BD71837_REG_PWRONCONFIG1 ; 
 int /*<<< orphan*/  BD71837_REG_REV ; 
 int /*<<< orphan*/  BD718XX_PWRBTN_LONG_PRESS_10S ; 
 int /*<<< orphan*/  BD718XX_PWRBTN_PRESS_DURATION_MASK ; 
 int /*<<< orphan*/  BD718XX_PWRBTN_SHORT_PRESS_10MS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd71837_irq_chip ; 
 unsigned int* bd71837_mfd_cells ; 
 int /*<<< orphan*/  bd71837_regmap_config ; 
 TYPE_1__ button ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct bd71837*) ; 
 struct bd71837* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* supported_revisions ; 

__attribute__((used)) static int bd71837_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct bd71837 *bd71837;
	int ret, i;
	unsigned int val;

	bd71837 = devm_kzalloc(&i2c->dev, sizeof(struct bd71837), GFP_KERNEL);

	if (!bd71837)
		return -ENOMEM;

	bd71837->chip_irq = i2c->irq;

	if (!bd71837->chip_irq) {
		dev_err(&i2c->dev, "No IRQ configured\n");
		return -EINVAL;
	}

	bd71837->dev = &i2c->dev;
	dev_set_drvdata(&i2c->dev, bd71837);

	bd71837->regmap = devm_regmap_init_i2c(i2c, &bd71837_regmap_config);
	if (IS_ERR(bd71837->regmap)) {
		dev_err(&i2c->dev, "regmap initialization failed\n");
		return PTR_ERR(bd71837->regmap);
	}

	ret = regmap_read(bd71837->regmap, BD71837_REG_REV, &val);
	if (ret) {
		dev_err(&i2c->dev, "Read BD71837_REG_DEVICE failed\n");
		return ret;
	}
	for (i = 0; i < ARRAY_SIZE(supported_revisions); i++)
		if (supported_revisions[i] == val)
			break;

	if (i == ARRAY_SIZE(supported_revisions)) {
		dev_err(&i2c->dev, "Unsupported chip revision\n");
		return -ENODEV;
	}

	ret = devm_regmap_add_irq_chip(&i2c->dev, bd71837->regmap,
				       bd71837->chip_irq, IRQF_ONESHOT, 0,
				       &bd71837_irq_chip, &bd71837->irq_data);
	if (ret) {
		dev_err(&i2c->dev, "Failed to add irq_chip\n");
		return ret;
	}

	/* Configure short press to 10 milliseconds */
	ret = regmap_update_bits(bd71837->regmap,
				 BD71837_REG_PWRONCONFIG0,
				 BD718XX_PWRBTN_PRESS_DURATION_MASK,
				 BD718XX_PWRBTN_SHORT_PRESS_10MS);
	if (ret) {
		dev_err(&i2c->dev,
			"Failed to configure button short press timeout\n");
		return ret;
	}

	/* Configure long press to 10 seconds */
	ret = regmap_update_bits(bd71837->regmap,
				 BD71837_REG_PWRONCONFIG1,
				 BD718XX_PWRBTN_PRESS_DURATION_MASK,
				 BD718XX_PWRBTN_LONG_PRESS_10S);

	if (ret) {
		dev_err(&i2c->dev,
			"Failed to configure button long press timeout\n");
		return ret;
	}

	ret = regmap_irq_get_virq(bd71837->irq_data, BD71837_INT_PWRBTN_S);

	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to get the IRQ\n");
		return ret;
	}

	button.irq = ret;

	ret = devm_mfd_add_devices(bd71837->dev, PLATFORM_DEVID_AUTO,
				   bd71837_mfd_cells,
				   ARRAY_SIZE(bd71837_mfd_cells), NULL, 0,
				   regmap_irq_get_domain(bd71837->irq_data));
	if (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	return ret;
}