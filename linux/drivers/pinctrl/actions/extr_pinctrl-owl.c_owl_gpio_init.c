#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct gpio_irq_chip {int /*<<< orphan*/ * parents; int /*<<< orphan*/ * map; int /*<<< orphan*/  num_parents; struct owl_pinctrl* parent_handler_data; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  handler; TYPE_2__* chip; } ;
struct gpio_chip {int base; int /*<<< orphan*/  ngpio; struct gpio_irq_chip irq; TYPE_1__* of_node; int /*<<< orphan*/  owner; TYPE_4__* parent; int /*<<< orphan*/  label; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  name; } ;
struct owl_pinctrl {TYPE_4__* dev; struct gpio_chip chip; TYPE_3__* soc; int /*<<< orphan*/ * irq; int /*<<< orphan*/  num_irq; TYPE_2__ irq_chip; } ;
struct owl_gpio_port {int pins; } ;
struct TYPE_10__ {TYPE_1__* of_node; } ;
struct TYPE_9__ {int nports; struct owl_gpio_port* ports; int /*<<< orphan*/  ngpios; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (struct gpio_chip*,struct owl_pinctrl*) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  owl_gpio_irq_ack ; 
 int /*<<< orphan*/  owl_gpio_irq_handler ; 
 int /*<<< orphan*/  owl_gpio_irq_mask ; 
 int /*<<< orphan*/  owl_gpio_irq_set_type ; 
 int /*<<< orphan*/  owl_gpio_irq_unmask ; 

__attribute__((used)) static int owl_gpio_init(struct owl_pinctrl *pctrl)
{
	struct gpio_chip *chip;
	struct gpio_irq_chip *gpio_irq;
	int ret, i, j, offset;

	chip = &pctrl->chip;
	chip->base = -1;
	chip->ngpio = pctrl->soc->ngpios;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->owner = THIS_MODULE;
	chip->of_node = pctrl->dev->of_node;

	pctrl->irq_chip.name = chip->of_node->name;
	pctrl->irq_chip.irq_ack = owl_gpio_irq_ack;
	pctrl->irq_chip.irq_mask = owl_gpio_irq_mask;
	pctrl->irq_chip.irq_unmask = owl_gpio_irq_unmask;
	pctrl->irq_chip.irq_set_type = owl_gpio_irq_set_type;

	gpio_irq = &chip->irq;
	gpio_irq->chip = &pctrl->irq_chip;
	gpio_irq->handler = handle_simple_irq;
	gpio_irq->default_type = IRQ_TYPE_NONE;
	gpio_irq->parent_handler = owl_gpio_irq_handler;
	gpio_irq->parent_handler_data = pctrl;
	gpio_irq->num_parents = pctrl->num_irq;
	gpio_irq->parents = pctrl->irq;

	gpio_irq->map = devm_kcalloc(pctrl->dev, chip->ngpio,
				sizeof(*gpio_irq->map), GFP_KERNEL);
	if (!gpio_irq->map)
		return -ENOMEM;

	for (i = 0, offset = 0; i < pctrl->soc->nports; i++) {
		const struct owl_gpio_port *port = &pctrl->soc->ports[i];

		for (j = 0; j < port->pins; j++)
			gpio_irq->map[offset + j] = gpio_irq->parents[i];

		offset += port->pins;
	}

	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	if (ret) {
		dev_err(pctrl->dev, "failed to register gpiochip\n");
		return ret;
	}

	return 0;
}