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
struct power_supply_desc {int num_properties; scalar_t__ name; int /*<<< orphan*/  type; int /*<<< orphan*/  get_property; int /*<<< orphan*/  properties; } ;
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; struct gpio_charger* drv_data; TYPE_1__* of_node; } ;
struct device {TYPE_1__* of_node; struct gpio_charger_platform_data* platform_data; } ;
struct platform_device {scalar_t__ name; struct device dev; } ;
struct gpio_desc {int dummy; } ;
struct gpio_charger_platform_data {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; int /*<<< orphan*/  type; scalar_t__ name; int /*<<< orphan*/  gpio; scalar_t__ gpio_active_low; } ;
struct gpio_charger {int charge_status_irq; struct gpio_desc* charge_status; struct gpio_desc* charger; struct gpio_desc* gpiod; void* irq; struct power_supply_desc charger_desc; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 unsigned long GPIOF_ACTIVE_LOW ; 
 unsigned long GPIOF_IN ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_charger* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_power_supply_register (struct device*,struct power_supply_desc*,struct power_supply_config*) ; 
 void* gpio_charger_get_irq (struct device*,struct gpio_desc*,struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_charger_get_property ; 
 int /*<<< orphan*/  gpio_charger_get_type (struct device*) ; 
 int /*<<< orphan*/  gpio_charger_properties ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpio_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_charger*) ; 

__attribute__((used)) static int gpio_charger_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct gpio_charger_platform_data *pdata = dev->platform_data;
	struct power_supply_config psy_cfg = {};
	struct gpio_charger *gpio_charger;
	struct power_supply_desc *charger_desc;
	struct gpio_desc *charge_status;
	int charge_status_irq;
	unsigned long flags;
	int ret;

	if (!pdata && !dev->of_node) {
		dev_err(dev, "No platform data\n");
		return -ENOENT;
	}

	gpio_charger = devm_kzalloc(dev, sizeof(*gpio_charger), GFP_KERNEL);
	if (!gpio_charger)
		return -ENOMEM;

	/*
	 * This will fetch a GPIO descriptor from device tree, ACPI or
	 * boardfile descriptor tables. It's good to try this first.
	 */
	gpio_charger->gpiod = devm_gpiod_get(dev, NULL, GPIOD_IN);

	/*
	 * If this fails and we're not using device tree, try the
	 * legacy platform data method.
	 */
	if (IS_ERR(gpio_charger->gpiod) && !dev->of_node) {
		/* Non-DT: use legacy GPIO numbers */
		if (!gpio_is_valid(pdata->gpio)) {
			dev_err(dev, "Invalid gpio pin in pdata\n");
			return -EINVAL;
		}
		flags = GPIOF_IN;
		if (pdata->gpio_active_low)
			flags |= GPIOF_ACTIVE_LOW;
		ret = devm_gpio_request_one(dev, pdata->gpio, flags,
					    dev_name(dev));
		if (ret) {
			dev_err(dev, "Failed to request gpio pin: %d\n", ret);
			return ret;
		}
		/* Then convert this to gpiod for now */
		gpio_charger->gpiod = gpio_to_desc(pdata->gpio);
	} else if (IS_ERR(gpio_charger->gpiod)) {
		/* Just try again if this happens */
		if (PTR_ERR(gpio_charger->gpiod) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_err(dev, "error getting GPIO descriptor\n");
		return PTR_ERR(gpio_charger->gpiod);
	}

	charge_status = devm_gpiod_get_optional(dev, "charge-status", GPIOD_IN);
	gpio_charger->charge_status = charge_status;
	if (IS_ERR(gpio_charger->charge_status))
		return PTR_ERR(gpio_charger->charge_status);

	charger_desc = &gpio_charger->charger_desc;
	charger_desc->properties = gpio_charger_properties;
	charger_desc->num_properties = ARRAY_SIZE(gpio_charger_properties);
	/* Remove POWER_SUPPLY_PROP_STATUS from the supported properties. */
	if (!gpio_charger->charge_status)
		charger_desc->num_properties -= 1;
	charger_desc->get_property = gpio_charger_get_property;

	psy_cfg.of_node = dev->of_node;
	psy_cfg.drv_data = gpio_charger;

	if (pdata) {
		charger_desc->name = pdata->name;
		charger_desc->type = pdata->type;
		psy_cfg.supplied_to = pdata->supplied_to;
		psy_cfg.num_supplicants = pdata->num_supplicants;
	} else {
		charger_desc->name = dev->of_node->name;
		charger_desc->type = gpio_charger_get_type(dev);
	}

	if (!charger_desc->name)
		charger_desc->name = pdev->name;

	gpio_charger->charger = devm_power_supply_register(dev, charger_desc,
							   &psy_cfg);
	if (IS_ERR(gpio_charger->charger)) {
		ret = PTR_ERR(gpio_charger->charger);
		dev_err(dev, "Failed to register power supply: %d\n", ret);
		return ret;
	}

	gpio_charger->irq = gpio_charger_get_irq(dev, gpio_charger->charger,
						 gpio_charger->gpiod);

	charge_status_irq = gpio_charger_get_irq(dev, gpio_charger->charger,
						 gpio_charger->charge_status);
	gpio_charger->charge_status_irq = charge_status_irq;

	platform_set_drvdata(pdev, gpio_charger);

	device_init_wakeup(dev, 1);

	return 0;
}