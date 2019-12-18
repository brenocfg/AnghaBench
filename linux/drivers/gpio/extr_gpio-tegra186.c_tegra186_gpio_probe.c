#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct tegra_gpio_port {unsigned int pins; size_t irq; int /*<<< orphan*/  name; } ;
struct gpio_irq_chip {unsigned int num_parents; int* parents; int* map; struct tegra_gpio* parent_handler_data; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  handler; int /*<<< orphan*/ * domain_ops; TYPE_2__* chip; } ;
struct TYPE_11__ {int base; int ngpio; char const* const* names; int of_gpio_n_cells; struct gpio_irq_chip irq; int /*<<< orphan*/  of_xlate; TYPE_1__* of_node; TYPE_4__* parent; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  label; } ;
struct TYPE_13__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  name; } ;
struct tegra_gpio {int num_irq; int* irq; TYPE_10__ gpio; TYPE_3__* soc; TYPE_2__ intc; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_15__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_14__ {unsigned int num_ports; struct tegra_gpio_port* ports; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_4__*,TYPE_10__*,struct tegra_gpio*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 char* devm_kasprintf (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 void* devm_kcalloc (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 struct tegra_gpio* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 TYPE_3__* of_device_get_match_data (TYPE_4__*) ; 
 int platform_get_irq (struct platform_device*,unsigned int) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_gpio*) ; 
 int /*<<< orphan*/  tegra186_gpio_direction_input ; 
 int /*<<< orphan*/  tegra186_gpio_direction_output ; 
 int /*<<< orphan*/  tegra186_gpio_get ; 
 int /*<<< orphan*/  tegra186_gpio_get_direction ; 
 int /*<<< orphan*/  tegra186_gpio_irq ; 
 int /*<<< orphan*/  tegra186_gpio_irq_domain_ops ; 
 int /*<<< orphan*/  tegra186_gpio_of_xlate ; 
 int /*<<< orphan*/  tegra186_gpio_set ; 
 int /*<<< orphan*/  tegra186_irq_ack ; 
 int /*<<< orphan*/  tegra186_irq_mask ; 
 int /*<<< orphan*/  tegra186_irq_set_type ; 
 int /*<<< orphan*/  tegra186_irq_unmask ; 

__attribute__((used)) static int tegra186_gpio_probe(struct platform_device *pdev)
{
	unsigned int i, j, offset;
	struct gpio_irq_chip *irq;
	struct tegra_gpio *gpio;
	struct resource *res;
	char **names;
	int err;

	gpio = devm_kzalloc(&pdev->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	gpio->soc = of_device_get_match_data(&pdev->dev);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "gpio");
	gpio->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gpio->base))
		return PTR_ERR(gpio->base);

	err = platform_irq_count(pdev);
	if (err < 0)
		return err;

	gpio->num_irq = err;

	gpio->irq = devm_kcalloc(&pdev->dev, gpio->num_irq, sizeof(*gpio->irq),
				 GFP_KERNEL);
	if (!gpio->irq)
		return -ENOMEM;

	for (i = 0; i < gpio->num_irq; i++) {
		err = platform_get_irq(pdev, i);
		if (err < 0)
			return err;

		gpio->irq[i] = err;
	}

	gpio->gpio.label = gpio->soc->name;
	gpio->gpio.parent = &pdev->dev;

	gpio->gpio.get_direction = tegra186_gpio_get_direction;
	gpio->gpio.direction_input = tegra186_gpio_direction_input;
	gpio->gpio.direction_output = tegra186_gpio_direction_output;
	gpio->gpio.get = tegra186_gpio_get,
	gpio->gpio.set = tegra186_gpio_set;

	gpio->gpio.base = -1;

	for (i = 0; i < gpio->soc->num_ports; i++)
		gpio->gpio.ngpio += gpio->soc->ports[i].pins;

	names = devm_kcalloc(gpio->gpio.parent, gpio->gpio.ngpio,
			     sizeof(*names), GFP_KERNEL);
	if (!names)
		return -ENOMEM;

	for (i = 0, offset = 0; i < gpio->soc->num_ports; i++) {
		const struct tegra_gpio_port *port = &gpio->soc->ports[i];
		char *name;

		for (j = 0; j < port->pins; j++) {
			name = devm_kasprintf(gpio->gpio.parent, GFP_KERNEL,
					      "P%s.%02x", port->name, j);
			if (!name)
				return -ENOMEM;

			names[offset + j] = name;
		}

		offset += port->pins;
	}

	gpio->gpio.names = (const char * const *)names;

	gpio->gpio.of_node = pdev->dev.of_node;
	gpio->gpio.of_gpio_n_cells = 2;
	gpio->gpio.of_xlate = tegra186_gpio_of_xlate;

	gpio->intc.name = pdev->dev.of_node->name;
	gpio->intc.irq_ack = tegra186_irq_ack;
	gpio->intc.irq_mask = tegra186_irq_mask;
	gpio->intc.irq_unmask = tegra186_irq_unmask;
	gpio->intc.irq_set_type = tegra186_irq_set_type;

	irq = &gpio->gpio.irq;
	irq->chip = &gpio->intc;
	irq->domain_ops = &tegra186_gpio_irq_domain_ops;
	irq->handler = handle_simple_irq;
	irq->default_type = IRQ_TYPE_NONE;
	irq->parent_handler = tegra186_gpio_irq;
	irq->parent_handler_data = gpio;
	irq->num_parents = gpio->num_irq;
	irq->parents = gpio->irq;

	irq->map = devm_kcalloc(&pdev->dev, gpio->gpio.ngpio,
				sizeof(*irq->map), GFP_KERNEL);
	if (!irq->map)
		return -ENOMEM;

	for (i = 0, offset = 0; i < gpio->soc->num_ports; i++) {
		const struct tegra_gpio_port *port = &gpio->soc->ports[i];

		for (j = 0; j < port->pins; j++)
			irq->map[offset + j] = irq->parents[port->irq];

		offset += port->pins;
	}

	platform_set_drvdata(pdev, gpio);

	err = devm_gpiochip_add_data(&pdev->dev, &gpio->gpio, gpio);
	if (err < 0)
		return err;

	return 0;
}