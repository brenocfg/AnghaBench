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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct irq_chip {char const* name; int flags; int /*<<< orphan*/  irq_release_resources; int /*<<< orphan*/  irq_request_resources; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; } ;
struct gpio_chip {char const* label; int base; unsigned int ngpio; int /*<<< orphan*/  owner; struct device* parent; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  of_node; } ;
struct em_gio_priv {int /*<<< orphan*/  irq_domain; struct irq_chip irq_chip; struct gpio_chip gpio_chip; void* base1; void* base0; int /*<<< orphan*/  sense_lock; struct platform_device* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQCHIP_MASK_ON_SUSPEND ; 
 int IRQCHIP_SKIP_SET_WAKE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 char* dev_name (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct em_gio_priv*) ; 
 void* devm_ioremap_nocache (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct em_gio_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct em_gio_priv*) ; 
 int /*<<< orphan*/  em_gio_direction_input ; 
 int /*<<< orphan*/  em_gio_direction_output ; 
 int /*<<< orphan*/  em_gio_free ; 
 int /*<<< orphan*/  em_gio_get ; 
 int /*<<< orphan*/  em_gio_irq_disable ; 
 int /*<<< orphan*/  em_gio_irq_domain_ops ; 
 int /*<<< orphan*/  em_gio_irq_domain_remove ; 
 int /*<<< orphan*/  em_gio_irq_enable ; 
 int /*<<< orphan*/  em_gio_irq_handler ; 
 int /*<<< orphan*/  em_gio_irq_relres ; 
 int /*<<< orphan*/  em_gio_irq_reqres ; 
 int /*<<< orphan*/  em_gio_irq_set_type ; 
 int /*<<< orphan*/  em_gio_request ; 
 int /*<<< orphan*/  em_gio_set ; 
 int /*<<< orphan*/  em_gio_to_irq ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct em_gio_priv*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct em_gio_priv*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em_gio_probe(struct platform_device *pdev)
{
	struct em_gio_priv *p;
	struct resource *io[2], *irq[2];
	struct gpio_chip *gpio_chip;
	struct irq_chip *irq_chip;
	struct device *dev = &pdev->dev;
	const char *name = dev_name(dev);
	unsigned int ngpios;
	int ret;

	p = devm_kzalloc(dev, sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	p->pdev = pdev;
	platform_set_drvdata(pdev, p);
	spin_lock_init(&p->sense_lock);

	io[0] = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	io[1] = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	irq[0] = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	irq[1] = platform_get_resource(pdev, IORESOURCE_IRQ, 1);

	if (!io[0] || !io[1] || !irq[0] || !irq[1]) {
		dev_err(dev, "missing IRQ or IOMEM\n");
		return -EINVAL;
	}

	p->base0 = devm_ioremap_nocache(dev, io[0]->start,
					resource_size(io[0]));
	if (!p->base0)
		return -ENOMEM;

	p->base1 = devm_ioremap_nocache(dev, io[1]->start,
				   resource_size(io[1]));
	if (!p->base1)
		return -ENOMEM;

	if (of_property_read_u32(dev->of_node, "ngpios", &ngpios)) {
		dev_err(dev, "Missing ngpios OF property\n");
		return -EINVAL;
	}

	gpio_chip = &p->gpio_chip;
	gpio_chip->of_node = dev->of_node;
	gpio_chip->direction_input = em_gio_direction_input;
	gpio_chip->get = em_gio_get;
	gpio_chip->direction_output = em_gio_direction_output;
	gpio_chip->set = em_gio_set;
	gpio_chip->to_irq = em_gio_to_irq;
	gpio_chip->request = em_gio_request;
	gpio_chip->free = em_gio_free;
	gpio_chip->label = name;
	gpio_chip->parent = dev;
	gpio_chip->owner = THIS_MODULE;
	gpio_chip->base = -1;
	gpio_chip->ngpio = ngpios;

	irq_chip = &p->irq_chip;
	irq_chip->name = name;
	irq_chip->irq_mask = em_gio_irq_disable;
	irq_chip->irq_unmask = em_gio_irq_enable;
	irq_chip->irq_set_type = em_gio_irq_set_type;
	irq_chip->irq_request_resources = em_gio_irq_reqres;
	irq_chip->irq_release_resources = em_gio_irq_relres;
	irq_chip->flags	= IRQCHIP_SKIP_SET_WAKE | IRQCHIP_MASK_ON_SUSPEND;

	p->irq_domain = irq_domain_add_simple(dev->of_node, ngpios, 0,
					      &em_gio_irq_domain_ops, p);
	if (!p->irq_domain) {
		dev_err(dev, "cannot initialize irq domain\n");
		return -ENXIO;
	}

	ret = devm_add_action_or_reset(dev, em_gio_irq_domain_remove,
				       p->irq_domain);
	if (ret)
		return ret;

	if (devm_request_irq(dev, irq[0]->start,
			     em_gio_irq_handler, 0, name, p)) {
		dev_err(dev, "failed to request low IRQ\n");
		return -ENOENT;
	}

	if (devm_request_irq(dev, irq[1]->start,
			     em_gio_irq_handler, 0, name, p)) {
		dev_err(dev, "failed to request high IRQ\n");
		return -ENOENT;
	}

	ret = devm_gpiochip_add_data(dev, gpio_chip, p);
	if (ret) {
		dev_err(dev, "failed to add GPIO controller\n");
		return ret;
	}

	return 0;
}