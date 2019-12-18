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
struct slg51000 {int chip_irq; struct device* dev; struct gpio_desc* regmap; struct gpio_desc* cs_gpiod; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int irq; struct device dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_HIGH ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (struct device*,char*,int) ; 
 struct slg51000* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct slg51000*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct slg51000*) ; 
 int /*<<< orphan*/  slg51000_clear_fault_log (struct slg51000*) ; 
 int /*<<< orphan*/  slg51000_irq_handler ; 
 int /*<<< orphan*/  slg51000_regmap_config ; 
 int slg51000_regulator_init (struct slg51000*) ; 

__attribute__((used)) static int slg51000_i2c_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct slg51000 *chip;
	struct gpio_desc *cs_gpiod;
	int error, ret;

	chip = devm_kzalloc(dev, sizeof(struct slg51000), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	cs_gpiod = devm_gpiod_get_optional(dev, "dlg,cs",
					   GPIOD_OUT_HIGH |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	if (IS_ERR(cs_gpiod))
		return PTR_ERR(cs_gpiod);

	if (cs_gpiod) {
		dev_info(dev, "Found chip selector property\n");
		chip->cs_gpiod = cs_gpiod;
	}

	i2c_set_clientdata(client, chip);
	chip->chip_irq = client->irq;
	chip->dev = dev;
	chip->regmap = devm_regmap_init_i2c(client, &slg51000_regmap_config);
	if (IS_ERR(chip->regmap)) {
		error = PTR_ERR(chip->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n",
			error);
		return error;
	}

	ret = slg51000_regulator_init(chip);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to init regulator(%d)\n", ret);
		return ret;
	}

	slg51000_clear_fault_log(chip);

	if (chip->chip_irq) {
		ret = devm_request_threaded_irq(dev, chip->chip_irq, NULL,
						slg51000_irq_handler,
						(IRQF_TRIGGER_HIGH |
						IRQF_ONESHOT),
						"slg51000-irq", chip);
		if (ret != 0) {
			dev_err(dev, "Failed to request IRQ: %d\n",
				chip->chip_irq);
			return ret;
		}
	} else {
		dev_info(dev, "No IRQ configured\n");
	}

	return ret;
}