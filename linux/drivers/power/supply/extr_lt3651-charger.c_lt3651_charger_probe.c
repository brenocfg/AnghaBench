#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct power_supply_desc {int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct power_supply_config {struct lt3651_charger* drv_data; TYPE_1__* of_node; } ;
struct TYPE_11__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct lt3651_charger {void* charger; void* chrg_gpio; void* fault_gpio; void* acpr_gpio; struct power_supply_desc charger_desc; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_MAINS ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_gpiod_get (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct lt3651_charger* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* devm_power_supply_register (TYPE_2__*,struct power_supply_desc*,struct power_supply_config*) ; 
 int devm_request_any_context_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  lt3651_charger_get_property ; 
 int /*<<< orphan*/  lt3651_charger_irq ; 
 int /*<<< orphan*/  lt3651_charger_properties ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lt3651_charger*) ; 

__attribute__((used)) static int lt3651_charger_probe(struct platform_device *pdev)
{
	struct power_supply_config psy_cfg = {};
	struct lt3651_charger *lt3651_charger;
	struct power_supply_desc *charger_desc;
	int ret;

	lt3651_charger = devm_kzalloc(&pdev->dev, sizeof(*lt3651_charger),
					GFP_KERNEL);
	if (!lt3651_charger)
		return -ENOMEM;

	lt3651_charger->acpr_gpio = devm_gpiod_get(&pdev->dev,
					"lltc,acpr", GPIOD_IN);
	if (IS_ERR(lt3651_charger->acpr_gpio)) {
		ret = PTR_ERR(lt3651_charger->acpr_gpio);
		dev_err(&pdev->dev, "Failed to acquire acpr GPIO: %d\n", ret);
		return ret;
	}
	lt3651_charger->fault_gpio = devm_gpiod_get_optional(&pdev->dev,
					"lltc,fault", GPIOD_IN);
	if (IS_ERR(lt3651_charger->fault_gpio)) {
		ret = PTR_ERR(lt3651_charger->fault_gpio);
		dev_err(&pdev->dev, "Failed to acquire fault GPIO: %d\n", ret);
		return ret;
	}
	lt3651_charger->chrg_gpio = devm_gpiod_get_optional(&pdev->dev,
					"lltc,chrg", GPIOD_IN);
	if (IS_ERR(lt3651_charger->chrg_gpio)) {
		ret = PTR_ERR(lt3651_charger->chrg_gpio);
		dev_err(&pdev->dev, "Failed to acquire chrg GPIO: %d\n", ret);
		return ret;
	}

	charger_desc = &lt3651_charger->charger_desc;
	charger_desc->name = pdev->dev.of_node->name;
	charger_desc->type = POWER_SUPPLY_TYPE_MAINS;
	charger_desc->properties = lt3651_charger_properties;
	charger_desc->num_properties = ARRAY_SIZE(lt3651_charger_properties);
	charger_desc->get_property = lt3651_charger_get_property;
	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = lt3651_charger;

	lt3651_charger->charger = devm_power_supply_register(&pdev->dev,
						      charger_desc, &psy_cfg);
	if (IS_ERR(lt3651_charger->charger)) {
		ret = PTR_ERR(lt3651_charger->charger);
		dev_err(&pdev->dev, "Failed to register power supply: %d\n",
			ret);
		return ret;
	}

	/*
	 * Acquire IRQs for the GPIO pins if possible. If the system does not
	 * support IRQs on these pins, userspace will have to poll the sysfs
	 * files manually.
	 */
	if (lt3651_charger->acpr_gpio) {
		ret = gpiod_to_irq(lt3651_charger->acpr_gpio);
		if (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_charger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_charger->charger);
		if (ret < 0)
			dev_warn(&pdev->dev, "Failed to request acpr irq\n");
	}
	if (lt3651_charger->fault_gpio) {
		ret = gpiod_to_irq(lt3651_charger->fault_gpio);
		if (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_charger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_charger->charger);
		if (ret < 0)
			dev_warn(&pdev->dev, "Failed to request fault irq\n");
	}
	if (lt3651_charger->chrg_gpio) {
		ret = gpiod_to_irq(lt3651_charger->chrg_gpio);
		if (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_charger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_charger->charger);
		if (ret < 0)
			dev_warn(&pdev->dev, "Failed to request chrg irq\n");
	}

	platform_set_drvdata(pdev, lt3651_charger);

	return 0;
}