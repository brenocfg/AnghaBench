#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct axp20x_ac_power* drv_data; int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct axp_data {int /*<<< orphan*/  power_desc; scalar_t__ acin_adc; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap_irqc; } ;
struct axp20x_ac_power {void* supply; int /*<<< orphan*/  regmap; void* acin_i; void* acin_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  axp20x_ac_power_irq ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,char const* const,int) ; 
 void* devm_iio_channel_get (TYPE_1__*,char*) ; 
 struct axp20x_ac_power* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ ,struct power_supply_config*) ; 
 int devm_request_any_context_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct axp20x_ac_power*) ; 
 struct axp_data* of_device_get_match_data (TYPE_1__*) ; 
 int /*<<< orphan*/  of_device_is_available (int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char const* const) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axp20x_ac_power*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axp20x_ac_power_probe(struct platform_device *pdev)
{
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};
	struct axp20x_ac_power *power;
	const struct axp_data *axp_data;
	static const char * const irq_names[] = { "ACIN_PLUGIN", "ACIN_REMOVAL",
		NULL };
	int i, irq, ret;

	if (!of_device_is_available(pdev->dev.of_node))
		return -ENODEV;

	if (!axp20x) {
		dev_err(&pdev->dev, "Parent drvdata not set\n");
		return -EINVAL;
	}

	power = devm_kzalloc(&pdev->dev, sizeof(*power), GFP_KERNEL);
	if (!power)
		return -ENOMEM;

	axp_data = of_device_get_match_data(&pdev->dev);

	if (axp_data->acin_adc) {
		power->acin_v = devm_iio_channel_get(&pdev->dev, "acin_v");
		if (IS_ERR(power->acin_v)) {
			if (PTR_ERR(power->acin_v) == -ENODEV)
				return -EPROBE_DEFER;
			return PTR_ERR(power->acin_v);
		}

		power->acin_i = devm_iio_channel_get(&pdev->dev, "acin_i");
		if (IS_ERR(power->acin_i)) {
			if (PTR_ERR(power->acin_i) == -ENODEV)
				return -EPROBE_DEFER;
			return PTR_ERR(power->acin_i);
		}
	}

	power->regmap = dev_get_regmap(pdev->dev.parent, NULL);

	platform_set_drvdata(pdev, power);

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = power;

	power->supply = devm_power_supply_register(&pdev->dev,
						   axp_data->power_desc,
						   &psy_cfg);
	if (IS_ERR(power->supply))
		return PTR_ERR(power->supply);

	/* Request irqs after registering, as irqs may trigger immediately */
	for (i = 0; irq_names[i]; i++) {
		irq = platform_get_irq_byname(pdev, irq_names[i]);
		if (irq < 0) {
			dev_warn(&pdev->dev, "No IRQ for %s: %d\n",
				 irq_names[i], irq);
			continue;
		}
		irq = regmap_irq_get_virq(axp20x->regmap_irqc, irq);
		ret = devm_request_any_context_irq(&pdev->dev, irq,
						   axp20x_ac_power_irq, 0,
						   DRVNAME, power);
		if (ret < 0)
			dev_warn(&pdev->dev, "Error requesting %s IRQ: %d\n",
				 irq_names[i], ret);
	}

	return 0;
}