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
struct of_device_id {scalar_t__ data; } ;
struct device {scalar_t__ of_node; TYPE_1__* driver; } ;
struct axp20x_dev {long variant; int /*<<< orphan*/ * regmap_irq_chip; int /*<<< orphan*/ * regmap_cfg; void* cells; void* nr_cells; struct device* dev; int /*<<< orphan*/  irq_flags; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
#define  AXP152_ID 137 
#define  AXP202_ID 136 
#define  AXP209_ID 135 
#define  AXP221_ID 134 
#define  AXP223_ID 133 
#define  AXP288_ID 132 
#define  AXP803_ID 131 
#define  AXP806_ID 130 
#define  AXP809_ID 129 
#define  AXP813_ID 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 void* axp152_cells ; 
 int /*<<< orphan*/  axp152_regmap_config ; 
 int /*<<< orphan*/  axp152_regmap_irq_chip ; 
 void* axp20x_cells ; 
 int /*<<< orphan*/ * axp20x_model_names ; 
 int /*<<< orphan*/  axp20x_regmap_config ; 
 int /*<<< orphan*/  axp20x_regmap_irq_chip ; 
 void* axp221_cells ; 
 void* axp223_cells ; 
 int /*<<< orphan*/  axp22x_regmap_config ; 
 int /*<<< orphan*/  axp22x_regmap_irq_chip ; 
 void* axp288_cells ; 
 int /*<<< orphan*/  axp288_regmap_config ; 
 int /*<<< orphan*/  axp288_regmap_irq_chip ; 
 void* axp803_cells ; 
 int /*<<< orphan*/  axp803_regmap_irq_chip ; 
 void* axp806_cells ; 
 int /*<<< orphan*/  axp806_regmap_config ; 
 int /*<<< orphan*/  axp806_regmap_irq_chip ; 
 void* axp806_self_working_cells ; 
 void* axp809_cells ; 
 int /*<<< orphan*/  axp809_regmap_irq_chip ; 
 void* axp813_cells ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_property_read_bool (scalar_t__,char*) ; 

int axp20x_match_device(struct axp20x_dev *axp20x)
{
	struct device *dev = axp20x->dev;
	const struct acpi_device_id *acpi_id;
	const struct of_device_id *of_id;

	if (dev->of_node) {
		of_id = of_match_device(dev->driver->of_match_table, dev);
		if (!of_id) {
			dev_err(dev, "Unable to match OF ID\n");
			return -ENODEV;
		}
		axp20x->variant = (long)of_id->data;
	} else {
		acpi_id = acpi_match_device(dev->driver->acpi_match_table, dev);
		if (!acpi_id || !acpi_id->driver_data) {
			dev_err(dev, "Unable to match ACPI ID and data\n");
			return -ENODEV;
		}
		axp20x->variant = (long)acpi_id->driver_data;
	}

	switch (axp20x->variant) {
	case AXP152_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp152_cells);
		axp20x->cells = axp152_cells;
		axp20x->regmap_cfg = &axp152_regmap_config;
		axp20x->regmap_irq_chip = &axp152_regmap_irq_chip;
		break;
	case AXP202_ID:
	case AXP209_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp20x_cells);
		axp20x->cells = axp20x_cells;
		axp20x->regmap_cfg = &axp20x_regmap_config;
		axp20x->regmap_irq_chip = &axp20x_regmap_irq_chip;
		break;
	case AXP221_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp221_cells);
		axp20x->cells = axp221_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp22x_regmap_irq_chip;
		break;
	case AXP223_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp223_cells);
		axp20x->cells = axp223_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp22x_regmap_irq_chip;
		break;
	case AXP288_ID:
		axp20x->cells = axp288_cells;
		axp20x->nr_cells = ARRAY_SIZE(axp288_cells);
		axp20x->regmap_cfg = &axp288_regmap_config;
		axp20x->regmap_irq_chip = &axp288_regmap_irq_chip;
		axp20x->irq_flags = IRQF_TRIGGER_LOW;
		break;
	case AXP803_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp803_cells);
		axp20x->cells = axp803_cells;
		axp20x->regmap_cfg = &axp288_regmap_config;
		axp20x->regmap_irq_chip = &axp803_regmap_irq_chip;
		break;
	case AXP806_ID:
		if (of_property_read_bool(axp20x->dev->of_node,
					  "x-powers,self-working-mode")) {
			axp20x->nr_cells = ARRAY_SIZE(axp806_self_working_cells);
			axp20x->cells = axp806_self_working_cells;
		} else {
			axp20x->nr_cells = ARRAY_SIZE(axp806_cells);
			axp20x->cells = axp806_cells;
		}
		axp20x->regmap_cfg = &axp806_regmap_config;
		axp20x->regmap_irq_chip = &axp806_regmap_irq_chip;
		break;
	case AXP809_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp809_cells);
		axp20x->cells = axp809_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp809_regmap_irq_chip;
		break;
	case AXP813_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp813_cells);
		axp20x->cells = axp813_cells;
		axp20x->regmap_cfg = &axp288_regmap_config;
		/*
		 * The IRQ table given in the datasheet is incorrect.
		 * In IRQ enable/status registers 1, there are separate
		 * IRQs for ACIN and VBUS, instead of bits [7:5] being
		 * the same as bits [4:2]. So it shares the same IRQs
		 * as the AXP803, rather than the AXP288.
		 */
		axp20x->regmap_irq_chip = &axp803_regmap_irq_chip;
		break;
	default:
		dev_err(dev, "unsupported AXP20X ID %lu\n", axp20x->variant);
		return -EINVAL;
	}
	dev_info(dev, "AXP20x variant %s found\n",
		 axp20x_model_names[axp20x->variant]);

	return 0;
}