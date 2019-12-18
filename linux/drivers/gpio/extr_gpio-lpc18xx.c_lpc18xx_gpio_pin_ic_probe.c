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
struct resource {int dummy; } ;
struct lpc18xx_gpio_pin_ic {int /*<<< orphan*/  base; int /*<<< orphan*/  domain; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct device* parent; } ;
struct lpc18xx_gpio_chip {struct lpc18xx_gpio_pin_ic* pin_ic; TYPE_1__ gpio; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_LPC18XX_GPIO_PIN_IC_IRQS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_iounmap (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct lpc18xx_gpio_pin_ic*) ; 
 struct lpc18xx_gpio_pin_ic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_hierarchy (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lpc18xx_gpio_pin_ic*) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic_domain_ops ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int,struct resource*) ; 
 struct device_node* of_irq_find_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_match_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_gpio_pin_ic_probe(struct lpc18xx_gpio_chip *gc)
{
	struct device *dev = gc->gpio.parent;
	struct irq_domain *parent_domain;
	struct device_node *parent_node;
	struct lpc18xx_gpio_pin_ic *ic;
	struct resource res;
	int ret, index;

	parent_node = of_irq_find_parent(dev->of_node);
	if (!parent_node)
		return -ENXIO;

	parent_domain = irq_find_host(parent_node);
	of_node_put(parent_node);
	if (!parent_domain)
		return -ENXIO;

	ic = devm_kzalloc(dev, sizeof(*ic), GFP_KERNEL);
	if (!ic)
		return -ENOMEM;

	index = of_property_match_string(dev->of_node, "reg-names",
					 "gpio-pin-ic");
	if (index < 0) {
		ret = -ENODEV;
		goto free_ic;
	}

	ret = of_address_to_resource(dev->of_node, index, &res);
	if (ret < 0)
		goto free_ic;

	ic->base = devm_ioremap_resource(dev, &res);
	if (IS_ERR(ic->base)) {
		ret = PTR_ERR(ic->base);
		goto free_ic;
	}

	raw_spin_lock_init(&ic->lock);

	ic->domain = irq_domain_add_hierarchy(parent_domain, 0,
					      NR_LPC18XX_GPIO_PIN_IC_IRQS,
					      dev->of_node,
					      &lpc18xx_gpio_pin_ic_domain_ops,
					      ic);
	if (!ic->domain) {
		pr_err("unable to add irq domain\n");
		ret = -ENODEV;
		goto free_iomap;
	}

	gc->pin_ic = ic;

	return 0;

free_iomap:
	devm_iounmap(dev, ic->base);
free_ic:
	devm_kfree(dev, ic);

	return ret;
}