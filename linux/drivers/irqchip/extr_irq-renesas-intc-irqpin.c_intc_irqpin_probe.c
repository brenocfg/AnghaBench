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
struct resource {int start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct irq_chip {char* name; void (* irq_mask ) (struct irq_data*) ;void (* irq_unmask ) (struct irq_data*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; struct device* parent_device; } ;
struct intc_irqpin_priv {int sense_bitfield_width; int requested_irq; int shared_irqs; int /*<<< orphan*/  irq_domain; struct intc_irqpin_priv* irq; struct irq_chip irq_chip; struct intc_irqpin_iomem* iomem; struct intc_irqpin_priv* p; struct platform_device* pdev; } ;
struct intc_irqpin_iomem {int width; int /*<<< orphan*/  iomem; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct intc_irqpin_config {int /*<<< orphan*/  irlm_bit; scalar_t__ needs_irlm; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTC_IRQPIN_MAX ; 
 size_t INTC_IRQPIN_REG_IRLM ; 
 int INTC_IRQPIN_REG_NR ; 
 int INTC_IRQPIN_REG_NR_MANDATORY ; 
 int /*<<< orphan*/  INTC_IRQPIN_REG_SOURCE ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQCHIP_MASK_ON_SUSPEND ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (struct device*,int,int) ; 
 struct intc_irqpin_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct intc_irqpin_priv*) ; 
 void intc_irqpin_irq_disable (struct irq_data*) ; 
 void intc_irqpin_irq_disable_force (struct irq_data*) ; 
 int /*<<< orphan*/  intc_irqpin_irq_domain_ops ; 
 void intc_irqpin_irq_enable (struct irq_data*) ; 
 void intc_irqpin_irq_enable_force (struct irq_data*) ; 
 int /*<<< orphan*/  intc_irqpin_irq_handler ; 
 int /*<<< orphan*/  intc_irqpin_irq_set_type ; 
 int /*<<< orphan*/  intc_irqpin_irq_set_wake ; 
 int /*<<< orphan*/  intc_irqpin_mask_unmask_prio (struct intc_irqpin_priv*,int,int) ; 
 int /*<<< orphan*/  intc_irqpin_read32 ; 
 int /*<<< orphan*/  intc_irqpin_read8 ; 
 int /*<<< orphan*/  intc_irqpin_read_modify_write (struct intc_irqpin_priv*,size_t,int /*<<< orphan*/ ,int,int) ; 
 void intc_irqpin_shared_irq_disable (struct irq_data*) ; 
 void intc_irqpin_shared_irq_enable (struct irq_data*) ; 
 int /*<<< orphan*/  intc_irqpin_shared_irq_handler ; 
 int /*<<< orphan*/  intc_irqpin_write (struct intc_irqpin_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intc_irqpin_write32 ; 
 int /*<<< orphan*/  intc_irqpin_write8 ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct intc_irqpin_priv*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource**,int /*<<< orphan*/ ,int) ; 
 struct intc_irqpin_config* of_device_get_match_data (struct device*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intc_irqpin_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static int intc_irqpin_probe(struct platform_device *pdev)
{
	const struct intc_irqpin_config *config;
	struct device *dev = &pdev->dev;
	struct intc_irqpin_priv *p;
	struct intc_irqpin_iomem *i;
	struct resource *io[INTC_IRQPIN_REG_NR];
	struct resource *irq;
	struct irq_chip *irq_chip;
	void (*enable_fn)(struct irq_data *d);
	void (*disable_fn)(struct irq_data *d);
	const char *name = dev_name(dev);
	bool control_parent;
	unsigned int nirqs;
	int ref_irq;
	int ret;
	int k;

	p = devm_kzalloc(dev, sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	/* deal with driver instance configuration */
	of_property_read_u32(dev->of_node, "sense-bitfield-width",
			     &p->sense_bitfield_width);
	control_parent = of_property_read_bool(dev->of_node, "control-parent");
	if (!p->sense_bitfield_width)
		p->sense_bitfield_width = 4; /* default to 4 bits */

	p->pdev = pdev;
	platform_set_drvdata(pdev, p);

	config = of_device_get_match_data(dev);

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);

	/* get hold of register banks */
	memset(io, 0, sizeof(io));
	for (k = 0; k < INTC_IRQPIN_REG_NR; k++) {
		io[k] = platform_get_resource(pdev, IORESOURCE_MEM, k);
		if (!io[k] && k < INTC_IRQPIN_REG_NR_MANDATORY) {
			dev_err(dev, "not enough IOMEM resources\n");
			ret = -EINVAL;
			goto err0;
		}
	}

	/* allow any number of IRQs between 1 and INTC_IRQPIN_MAX */
	for (k = 0; k < INTC_IRQPIN_MAX; k++) {
		irq = platform_get_resource(pdev, IORESOURCE_IRQ, k);
		if (!irq)
			break;

		p->irq[k].p = p;
		p->irq[k].requested_irq = irq->start;
	}

	nirqs = k;
	if (nirqs < 1) {
		dev_err(dev, "not enough IRQ resources\n");
		ret = -EINVAL;
		goto err0;
	}

	/* ioremap IOMEM and setup read/write callbacks */
	for (k = 0; k < INTC_IRQPIN_REG_NR; k++) {
		i = &p->iomem[k];

		/* handle optional registers */
		if (!io[k])
			continue;

		switch (resource_size(io[k])) {
		case 1:
			i->width = 8;
			i->read = intc_irqpin_read8;
			i->write = intc_irqpin_write8;
			break;
		case 4:
			i->width = 32;
			i->read = intc_irqpin_read32;
			i->write = intc_irqpin_write32;
			break;
		default:
			dev_err(dev, "IOMEM size mismatch\n");
			ret = -EINVAL;
			goto err0;
		}

		i->iomem = devm_ioremap_nocache(dev, io[k]->start,
						resource_size(io[k]));
		if (!i->iomem) {
			dev_err(dev, "failed to remap IOMEM\n");
			ret = -ENXIO;
			goto err0;
		}
	}

	/* configure "individual IRQ mode" where needed */
	if (config && config->needs_irlm) {
		if (io[INTC_IRQPIN_REG_IRLM])
			intc_irqpin_read_modify_write(p, INTC_IRQPIN_REG_IRLM,
						      config->irlm_bit, 1, 1);
		else
			dev_warn(dev, "unable to select IRLM mode\n");
	}

	/* mask all interrupts using priority */
	for (k = 0; k < nirqs; k++)
		intc_irqpin_mask_unmask_prio(p, k, 1);

	/* clear all pending interrupts */
	intc_irqpin_write(p, INTC_IRQPIN_REG_SOURCE, 0x0);

	/* scan for shared interrupt lines */
	ref_irq = p->irq[0].requested_irq;
	p->shared_irqs = 1;
	for (k = 1; k < nirqs; k++) {
		if (ref_irq != p->irq[k].requested_irq) {
			p->shared_irqs = 0;
			break;
		}
	}

	/* use more severe masking method if requested */
	if (control_parent) {
		enable_fn = intc_irqpin_irq_enable_force;
		disable_fn = intc_irqpin_irq_disable_force;
	} else if (!p->shared_irqs) {
		enable_fn = intc_irqpin_irq_enable;
		disable_fn = intc_irqpin_irq_disable;
	} else {
		enable_fn = intc_irqpin_shared_irq_enable;
		disable_fn = intc_irqpin_shared_irq_disable;
	}

	irq_chip = &p->irq_chip;
	irq_chip->name = "intc-irqpin";
	irq_chip->parent_device = dev;
	irq_chip->irq_mask = disable_fn;
	irq_chip->irq_unmask = enable_fn;
	irq_chip->irq_set_type = intc_irqpin_irq_set_type;
	irq_chip->irq_set_wake = intc_irqpin_irq_set_wake;
	irq_chip->flags	= IRQCHIP_MASK_ON_SUSPEND;

	p->irq_domain = irq_domain_add_simple(dev->of_node, nirqs, 0,
					      &intc_irqpin_irq_domain_ops, p);
	if (!p->irq_domain) {
		ret = -ENXIO;
		dev_err(dev, "cannot initialize irq domain\n");
		goto err0;
	}

	if (p->shared_irqs) {
		/* request one shared interrupt */
		if (devm_request_irq(dev, p->irq[0].requested_irq,
				intc_irqpin_shared_irq_handler,
				IRQF_SHARED, name, p)) {
			dev_err(dev, "failed to request low IRQ\n");
			ret = -ENOENT;
			goto err1;
		}
	} else {
		/* request interrupts one by one */
		for (k = 0; k < nirqs; k++) {
			if (devm_request_irq(dev, p->irq[k].requested_irq,
					     intc_irqpin_irq_handler, 0, name,
					     &p->irq[k])) {
				dev_err(dev, "failed to request low IRQ\n");
				ret = -ENOENT;
				goto err1;
			}
		}
	}

	/* unmask all interrupts on prio level */
	for (k = 0; k < nirqs; k++)
		intc_irqpin_mask_unmask_prio(p, k, 0);

	dev_info(dev, "driving %d irqs\n", nirqs);

	return 0;

err1:
	irq_domain_remove(p->irq_domain);
err0:
	pm_runtime_put(dev);
	pm_runtime_disable(dev);
	return ret;
}