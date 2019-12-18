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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;
struct irq_chip {char* name; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_unmask; void* irq_mask; void* irq_disable; int /*<<< orphan*/  irq_ack; } ;
struct gpio_chip {int dummy; } ;
struct at91_gpio_chip {struct at91_gpio_chip* next; int /*<<< orphan*/  pioc_virq; int /*<<< orphan*/  chip; int /*<<< orphan*/  pioc_idx; scalar_t__ regbase; TYPE_1__* ops; int /*<<< orphan*/  pioc_hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ PIO_IDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct irq_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_irq_ack ; 
 int /*<<< orphan*/  gpio_irq_handler ; 
 void* gpio_irq_mask ; 
 int /*<<< orphan*/  gpio_irq_set_wake ; 
 int /*<<< orphan*/  gpio_irq_unmask ; 
 struct at91_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int gpiochip_irqchip_add (int /*<<< orphan*/ *,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (int /*<<< orphan*/ *,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 struct gpio_chip* irq_get_handler_data (int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int at91_gpio_of_irq_setup(struct platform_device *pdev,
				  struct at91_gpio_chip *at91_gpio)
{
	struct gpio_chip	*gpiochip_prev = NULL;
	struct at91_gpio_chip   *prev = NULL;
	struct irq_data		*d = irq_get_irq_data(at91_gpio->pioc_virq);
	struct irq_chip		*gpio_irqchip;
	int ret, i;

	gpio_irqchip = devm_kzalloc(&pdev->dev, sizeof(*gpio_irqchip), GFP_KERNEL);
	if (!gpio_irqchip)
		return -ENOMEM;

	at91_gpio->pioc_hwirq = irqd_to_hwirq(d);

	gpio_irqchip->name = "GPIO";
	gpio_irqchip->irq_ack = gpio_irq_ack;
	gpio_irqchip->irq_disable = gpio_irq_mask;
	gpio_irqchip->irq_mask = gpio_irq_mask;
	gpio_irqchip->irq_unmask = gpio_irq_unmask;
	gpio_irqchip->irq_set_wake = gpio_irq_set_wake,
	gpio_irqchip->irq_set_type = at91_gpio->ops->irq_type;

	/* Disable irqs of this PIO controller */
	writel_relaxed(~0, at91_gpio->regbase + PIO_IDR);

	/*
	 * Let the generic code handle this edge IRQ, the the chained
	 * handler will perform the actual work of handling the parent
	 * interrupt.
	 */
	ret = gpiochip_irqchip_add(&at91_gpio->chip,
				   gpio_irqchip,
				   0,
				   handle_edge_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_err(&pdev->dev, "at91_gpio.%d: Couldn't add irqchip to gpiochip.\n",
			at91_gpio->pioc_idx);
		return ret;
	}

	/* The top level handler handles one bank of GPIOs, except
	 * on some SoC it can handle up to three...
	 * We only set up the handler for the first of the list.
	 */
	gpiochip_prev = irq_get_handler_data(at91_gpio->pioc_virq);
	if (!gpiochip_prev) {
		/* Then register the chain on the parent IRQ */
		gpiochip_set_chained_irqchip(&at91_gpio->chip,
					     gpio_irqchip,
					     at91_gpio->pioc_virq,
					     gpio_irq_handler);
		return 0;
	}

	prev = gpiochip_get_data(gpiochip_prev);

	/* we can only have 2 banks before */
	for (i = 0; i < 2; i++) {
		if (prev->next) {
			prev = prev->next;
		} else {
			prev->next = at91_gpio;
			return 0;
		}
	}

	return -EINVAL;
}