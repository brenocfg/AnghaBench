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
struct x86_cpu_id {scalar_t__ driver_data; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct irq_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  init_valid_mask; } ;
struct gpio_chip {int base; TYPE_1__ irq; scalar_t__ ngpio; int /*<<< orphan*/  direction_output; void* direction_input; int /*<<< orphan*/  set; void* get; int /*<<< orphan*/  owner; struct device* parent; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPE0A_PME_B0_VIRT_GPIO_PIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,int /*<<< orphan*/ *) ; 
 struct gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gpio_chip*) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,struct irq_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  int0002_cpu_ids ; 
 int /*<<< orphan*/  int0002_gpio_direction_output ; 
 void* int0002_gpio_get ; 
 int /*<<< orphan*/  int0002_gpio_set ; 
 int /*<<< orphan*/  int0002_init_irq_valid_mask ; 
 int /*<<< orphan*/  int0002_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct x86_cpu_id* x86_match_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int0002_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct x86_cpu_id *cpu_id;
	struct irq_chip *irq_chip;
	struct gpio_chip *chip;
	int irq, ret;

	/* Menlow has a different INT0002 device? <sigh> */
	cpu_id = x86_match_cpu(int0002_cpu_ids);
	if (!cpu_id)
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->label = DRV_NAME;
	chip->parent = dev;
	chip->owner = THIS_MODULE;
	chip->get = int0002_gpio_get;
	chip->set = int0002_gpio_set;
	chip->direction_input = int0002_gpio_get;
	chip->direction_output = int0002_gpio_direction_output;
	chip->base = -1;
	chip->ngpio = GPE0A_PME_B0_VIRT_GPIO_PIN + 1;
	chip->irq.init_valid_mask = int0002_init_irq_valid_mask;

	ret = devm_gpiochip_add_data(&pdev->dev, chip, NULL);
	if (ret) {
		dev_err(dev, "Error adding gpio chip: %d\n", ret);
		return ret;
	}

	/*
	 * We manually request the irq here instead of passing a flow-handler
	 * to gpiochip_set_chained_irqchip, because the irq is shared.
	 */
	ret = devm_request_irq(dev, irq, int0002_irq,
			       IRQF_SHARED, "INT0002", chip);
	if (ret) {
		dev_err(dev, "Error requesting IRQ %d: %d\n", irq, ret);
		return ret;
	}

	irq_chip = (struct irq_chip *)cpu_id->driver_data;

	ret = gpiochip_irqchip_add(chip, irq_chip, 0, handle_edge_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_err(dev, "Error adding irqchip: %d\n", ret);
		return ret;
	}

	gpiochip_set_chained_irqchip(chip, irq_chip, irq, NULL);

	device_init_wakeup(dev, true);
	return 0;
}