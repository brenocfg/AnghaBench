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
struct gpio_irq_chip {int num_parents; int* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/ * chip; } ;
struct TYPE_2__ {int base; int ngpio; struct gpio_irq_chip irq; int /*<<< orphan*/  owner; struct device* parent; int /*<<< orphan*/  label; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; } ;
struct zx_gpio {TYPE_1__ gc; scalar_t__ base; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ ZX_GPIO_IE ; 
 scalar_t__ ZX_GPIO_IM ; 
 int ZX_GPIO_NR ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct zx_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct zx_gpio*) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx_gpio*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  zx_direction_input ; 
 int /*<<< orphan*/  zx_direction_output ; 
 int /*<<< orphan*/  zx_get_value ; 
 int /*<<< orphan*/  zx_irq_handler ; 
 int /*<<< orphan*/  zx_irqchip ; 
 int /*<<< orphan*/  zx_set_value ; 

__attribute__((used)) static int zx_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct zx_gpio *chip;
	struct gpio_irq_chip *girq;
	int irq, id, ret;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(chip->base))
		return PTR_ERR(chip->base);

	raw_spin_lock_init(&chip->lock);
	if (of_property_read_bool(dev->of_node, "gpio-ranges")) {
		chip->gc.request = gpiochip_generic_request;
		chip->gc.free = gpiochip_generic_free;
	}

	id = of_alias_get_id(dev->of_node, "gpio");
	chip->gc.direction_input = zx_direction_input;
	chip->gc.direction_output = zx_direction_output;
	chip->gc.get = zx_get_value;
	chip->gc.set = zx_set_value;
	chip->gc.base = ZX_GPIO_NR * id;
	chip->gc.ngpio = ZX_GPIO_NR;
	chip->gc.label = dev_name(dev);
	chip->gc.parent = dev;
	chip->gc.owner = THIS_MODULE;

	/*
	 * irq_chip support
	 */
	writew_relaxed(0xffff, chip->base + ZX_GPIO_IM);
	writew_relaxed(0, chip->base + ZX_GPIO_IE);
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	girq = &chip->gc.irq;
	girq->chip = &zx_irqchip;
	girq->parent_handler = zx_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(&pdev->dev, 1,
				     sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents)
		return -ENOMEM;
	girq->parents[0] = irq;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;

	ret = gpiochip_add_data(&chip->gc, chip);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, chip);
	dev_info(dev, "ZX GPIO chip registered\n");

	return 0;
}