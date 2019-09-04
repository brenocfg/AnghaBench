#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; scalar_t__ name; } ;
struct TYPE_6__ {int base; int ngpio; scalar_t__ label; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  owner; int /*<<< orphan*/  of_node; struct device* parent; } ;
struct ingenic_gpio_chip {int reg_base; int version; int /*<<< orphan*/  irq; TYPE_2__ irq_chip; TYPE_1__ gc; int /*<<< orphan*/  map; } ;
typedef  enum jz_version { ____Placeholder_jz_version } jz_version ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQCHIP_MASK_ON_SUSPEND ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct ingenic_gpio_chip*) ; 
 scalar_t__ devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,char) ; 
 struct ingenic_gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int gpiochip_irqchip_add (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  ingenic_gpio_direction_input ; 
 int /*<<< orphan*/  ingenic_gpio_direction_output ; 
 int /*<<< orphan*/  ingenic_gpio_get ; 
 int /*<<< orphan*/  ingenic_gpio_irq_ack ; 
 int /*<<< orphan*/  ingenic_gpio_irq_disable ; 
 int /*<<< orphan*/  ingenic_gpio_irq_enable ; 
 int /*<<< orphan*/  ingenic_gpio_irq_handler ; 
 int /*<<< orphan*/  ingenic_gpio_irq_mask ; 
 int /*<<< orphan*/  ingenic_gpio_irq_set_type ; 
 int /*<<< orphan*/  ingenic_gpio_irq_set_wake ; 
 int /*<<< orphan*/  ingenic_gpio_irq_unmask ; 
 int /*<<< orphan*/  ingenic_gpio_set ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int ingenic_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ingenic_gpio_chip *jzgc;
	u32 bank;
	int err;

	jzgc = devm_kzalloc(dev, sizeof(*jzgc), GFP_KERNEL);
	if (!jzgc)
		return -ENOMEM;

	jzgc->map = dev_get_drvdata(dev->parent);
	if (!jzgc->map) {
		dev_err(dev, "Cannot get parent regmap\n");
		return -ENXIO;
	}

	err = of_property_read_u32(dev->of_node, "reg", &bank);
	if (err) {
		dev_err(dev, "Cannot read \"reg\" property: %i\n", err);
		return err;
	}

	jzgc->reg_base = bank * 0x100;

	jzgc->gc.label = devm_kasprintf(dev, GFP_KERNEL, "GPIO%c", 'A' + bank);
	if (!jzgc->gc.label)
		return -ENOMEM;

	/* DO NOT EXPAND THIS: FOR BACKWARD GPIO NUMBERSPACE COMPATIBIBILITY
	 * ONLY: WORK TO TRANSITION CONSUMERS TO USE THE GPIO DESCRIPTOR API IN
	 * <linux/gpio/consumer.h> INSTEAD.
	 */
	jzgc->gc.base = bank * 32;

	jzgc->gc.ngpio = 32;
	jzgc->gc.parent = dev;
	jzgc->gc.of_node = dev->of_node;
	jzgc->gc.owner = THIS_MODULE;
	jzgc->version = (enum jz_version)of_device_get_match_data(dev);

	jzgc->gc.set = ingenic_gpio_set;
	jzgc->gc.get = ingenic_gpio_get;
	jzgc->gc.direction_input = ingenic_gpio_direction_input;
	jzgc->gc.direction_output = ingenic_gpio_direction_output;

	if (of_property_read_bool(dev->of_node, "gpio-ranges")) {
		jzgc->gc.request = gpiochip_generic_request;
		jzgc->gc.free = gpiochip_generic_free;
	}

	err = devm_gpiochip_add_data(dev, &jzgc->gc, jzgc);
	if (err)
		return err;

	jzgc->irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!jzgc->irq)
		return -EINVAL;

	jzgc->irq_chip.name = jzgc->gc.label;
	jzgc->irq_chip.irq_enable = ingenic_gpio_irq_enable;
	jzgc->irq_chip.irq_disable = ingenic_gpio_irq_disable;
	jzgc->irq_chip.irq_unmask = ingenic_gpio_irq_unmask;
	jzgc->irq_chip.irq_mask = ingenic_gpio_irq_mask;
	jzgc->irq_chip.irq_ack = ingenic_gpio_irq_ack;
	jzgc->irq_chip.irq_set_type = ingenic_gpio_irq_set_type;
	jzgc->irq_chip.irq_set_wake = ingenic_gpio_irq_set_wake;
	jzgc->irq_chip.flags = IRQCHIP_MASK_ON_SUSPEND;

	err = gpiochip_irqchip_add(&jzgc->gc, &jzgc->irq_chip, 0,
			handle_level_irq, IRQ_TYPE_NONE);
	if (err)
		return err;

	gpiochip_set_chained_irqchip(&jzgc->gc, &jzgc->irq_chip,
			jzgc->irq, ingenic_gpio_irq_handler);
	return 0;
}