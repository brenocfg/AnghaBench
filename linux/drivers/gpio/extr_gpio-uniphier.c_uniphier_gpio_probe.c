#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct irq_chip {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_set_affinity; int /*<<< orphan*/  irq_eoi; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; void* name; } ;
struct gpio_chip {int base; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; struct device* parent; void* label; } ;
struct uniphier_gpio_priv {int /*<<< orphan*/  domain; struct irq_chip irq_chip; struct gpio_chip chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPHIER_GPIO_IRQ_MAX_NUM ; 
 void* dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct uniphier_gpio_priv*) ; 
 struct uniphier_gpio_priv* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int /*<<< orphan*/  irq_chip_eoi_parent ; 
 int /*<<< orphan*/  irq_chip_set_affinity_parent ; 
 int /*<<< orphan*/  irq_domain_create_hierarchy (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uniphier_gpio_priv*) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 struct device_node* of_irq_find_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_gpio_priv*) ; 
 int /*<<< orphan*/  saved_vals ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct uniphier_gpio_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uniphier_gpio_direction_input ; 
 int /*<<< orphan*/  uniphier_gpio_direction_output ; 
 int /*<<< orphan*/  uniphier_gpio_get ; 
 int /*<<< orphan*/  uniphier_gpio_get_direction ; 
 int uniphier_gpio_get_nbanks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_gpio_hw_init (struct uniphier_gpio_priv*) ; 
 int /*<<< orphan*/  uniphier_gpio_irq_domain_ops ; 
 int /*<<< orphan*/  uniphier_gpio_irq_mask ; 
 int /*<<< orphan*/  uniphier_gpio_irq_set_type ; 
 int /*<<< orphan*/  uniphier_gpio_irq_unmask ; 
 int /*<<< orphan*/  uniphier_gpio_set ; 
 int /*<<< orphan*/  uniphier_gpio_set_multiple ; 
 int /*<<< orphan*/  uniphier_gpio_to_irq ; 

__attribute__((used)) static int uniphier_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *parent_np;
	struct irq_domain *parent_domain;
	struct uniphier_gpio_priv *priv;
	struct gpio_chip *chip;
	struct irq_chip *irq_chip;
	unsigned int nregs;
	u32 ngpios;
	int ret;

	parent_np = of_irq_find_parent(dev->of_node);
	if (!parent_np)
		return -ENXIO;

	parent_domain = irq_find_host(parent_np);
	of_node_put(parent_np);
	if (!parent_domain)
		return -EPROBE_DEFER;

	ret = of_property_read_u32(dev->of_node, "ngpios", &ngpios);
	if (ret)
		return ret;

	nregs = uniphier_gpio_get_nbanks(ngpios) * 2 + 3;
	priv = devm_kzalloc(dev, struct_size(priv, saved_vals, nregs),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->regs))
		return PTR_ERR(priv->regs);

	spin_lock_init(&priv->lock);

	chip = &priv->chip;
	chip->label = dev_name(dev);
	chip->parent = dev;
	chip->request = gpiochip_generic_request;
	chip->free = gpiochip_generic_free;
	chip->get_direction = uniphier_gpio_get_direction;
	chip->direction_input = uniphier_gpio_direction_input;
	chip->direction_output = uniphier_gpio_direction_output;
	chip->get = uniphier_gpio_get;
	chip->set = uniphier_gpio_set;
	chip->set_multiple = uniphier_gpio_set_multiple;
	chip->to_irq = uniphier_gpio_to_irq;
	chip->base = -1;
	chip->ngpio = ngpios;

	irq_chip = &priv->irq_chip;
	irq_chip->name = dev_name(dev);
	irq_chip->irq_mask = uniphier_gpio_irq_mask;
	irq_chip->irq_unmask = uniphier_gpio_irq_unmask;
	irq_chip->irq_eoi = irq_chip_eoi_parent;
	irq_chip->irq_set_affinity = irq_chip_set_affinity_parent;
	irq_chip->irq_set_type = uniphier_gpio_irq_set_type;

	uniphier_gpio_hw_init(priv);

	ret = devm_gpiochip_add_data(dev, chip, priv);
	if (ret)
		return ret;

	priv->domain = irq_domain_create_hierarchy(
					parent_domain, 0,
					UNIPHIER_GPIO_IRQ_MAX_NUM,
					of_node_to_fwnode(dev->of_node),
					&uniphier_gpio_irq_domain_ops, priv);
	if (!priv->domain)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	return 0;
}