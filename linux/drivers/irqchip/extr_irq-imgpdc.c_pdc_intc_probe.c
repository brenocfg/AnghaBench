#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct pdc_intc_priv {unsigned int nr_perips; unsigned int nr_syswakes; int* perip_irqs; int syswake_irq; int /*<<< orphan*/  domain; scalar_t__ pdc_base; int /*<<< orphan*/  lock; } ;
struct irq_chip_generic {int unused; TYPE_3__* chip_types; scalar_t__ reg_base; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {void* flags; void* irq_set_wake; void* irq_set_type; void* irq_unmask; void* irq_mask; void* irq_ack; } ;
struct TYPE_9__ {void* mask; void* ack; } ;
struct TYPE_11__ {TYPE_2__ chip; TYPE_1__ regs; int /*<<< orphan*/  handler; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 void* IRQCHIP_MASK_ON_SUSPEND ; 
 int /*<<< orphan*/  IRQ_GC_INIT_NESTED_LOCK ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_MASK ; 
 void* PDC_IRQ_CLEAR ; 
 void* PDC_IRQ_ENABLE ; 
 void* PDC_IRQ_ROUTE ; 
 scalar_t__ SYS0_HWIRQ ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,unsigned int,unsigned int) ; 
 scalar_t__ devm_ioremap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* devm_kcalloc (TYPE_4__*,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct pdc_intc_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_alloc_domain_generic_chips (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int,int /*<<< orphan*/ *,struct pdc_intc_priv*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 void* irq_gc_ack_set_bit ; 
 void* irq_gc_mask_clr_bit ; 
 void* irq_gc_mask_set_bit ; 
 int /*<<< orphan*/  irq_generic_chip_ops ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct pdc_intc_priv*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pdc_intc_perip_isr ; 
 int /*<<< orphan*/  pdc_intc_setup (struct pdc_intc_priv*) ; 
 int /*<<< orphan*/  pdc_intc_syswake_isr ; 
 void* pdc_irq_set_wake ; 
 void* perip_irq_mask ; 
 void* perip_irq_unmask ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pdc_intc_priv*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 void* syswake_irq_set_type ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pdc_intc_probe(struct platform_device *pdev)
{
	struct pdc_intc_priv *priv;
	struct device_node *node = pdev->dev.of_node;
	struct resource *res_regs;
	struct irq_chip_generic *gc;
	unsigned int i;
	int irq, ret;
	u32 val;

	if (!node)
		return -ENOENT;

	/* Get registers */
	res_regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res_regs == NULL) {
		dev_err(&pdev->dev, "cannot find registers resource\n");
		return -ENOENT;
	}

	/* Allocate driver data */
	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "cannot allocate device data\n");
		return -ENOMEM;
	}
	raw_spin_lock_init(&priv->lock);
	platform_set_drvdata(pdev, priv);

	/* Ioremap the registers */
	priv->pdc_base = devm_ioremap(&pdev->dev, res_regs->start,
				      resource_size(res_regs));
	if (!priv->pdc_base)
		return -EIO;

	/* Get number of peripherals */
	ret = of_property_read_u32(node, "num-perips", &val);
	if (ret) {
		dev_err(&pdev->dev, "No num-perips node property found\n");
		return -EINVAL;
	}
	if (val > SYS0_HWIRQ) {
		dev_err(&pdev->dev, "num-perips (%u) out of range\n", val);
		return -EINVAL;
	}
	priv->nr_perips = val;

	/* Get number of syswakes */
	ret = of_property_read_u32(node, "num-syswakes", &val);
	if (ret) {
		dev_err(&pdev->dev, "No num-syswakes node property found\n");
		return -EINVAL;
	}
	if (val > SYS0_HWIRQ) {
		dev_err(&pdev->dev, "num-syswakes (%u) out of range\n", val);
		return -EINVAL;
	}
	priv->nr_syswakes = val;

	/* Get peripheral IRQ numbers */
	priv->perip_irqs = devm_kcalloc(&pdev->dev, 4, priv->nr_perips,
					GFP_KERNEL);
	if (!priv->perip_irqs) {
		dev_err(&pdev->dev, "cannot allocate perip IRQ list\n");
		return -ENOMEM;
	}
	for (i = 0; i < priv->nr_perips; ++i) {
		irq = platform_get_irq(pdev, 1 + i);
		if (irq < 0)
			return irq;
		priv->perip_irqs[i] = irq;
	}
	/* check if too many were provided */
	if (platform_get_irq(pdev, 1 + i) >= 0) {
		dev_err(&pdev->dev, "surplus perip IRQs detected\n");
		return -EINVAL;
	}

	/* Get syswake IRQ number */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	priv->syswake_irq = irq;

	/* Set up an IRQ domain */
	priv->domain = irq_domain_add_linear(node, 16, &irq_generic_chip_ops,
					     priv);
	if (unlikely(!priv->domain)) {
		dev_err(&pdev->dev, "cannot add IRQ domain\n");
		return -ENOMEM;
	}

	/*
	 * Set up 2 generic irq chips with 2 chip types.
	 * The first one for peripheral irqs (only 1 chip type used)
	 * The second one for syswake irqs (edge and level chip types)
	 */
	ret = irq_alloc_domain_generic_chips(priv->domain, 8, 2, "pdc",
					     handle_level_irq, 0, 0,
					     IRQ_GC_INIT_NESTED_LOCK);
	if (ret)
		goto err_generic;

	/* peripheral interrupt chip */

	gc = irq_get_domain_generic_chip(priv->domain, 0);
	gc->unused	= ~(BIT(priv->nr_perips) - 1);
	gc->reg_base	= priv->pdc_base;
	/*
	 * IRQ_ROUTE contains wake bits, so we can't use the generic versions as
	 * they cache the mask
	 */
	gc->chip_types[0].regs.mask		= PDC_IRQ_ROUTE;
	gc->chip_types[0].chip.irq_mask		= perip_irq_mask;
	gc->chip_types[0].chip.irq_unmask	= perip_irq_unmask;
	gc->chip_types[0].chip.irq_set_wake	= pdc_irq_set_wake;

	/* syswake interrupt chip */

	gc = irq_get_domain_generic_chip(priv->domain, 8);
	gc->unused	= ~(BIT(priv->nr_syswakes) - 1);
	gc->reg_base	= priv->pdc_base;

	/* edge interrupts */
	gc->chip_types[0].type			= IRQ_TYPE_EDGE_BOTH;
	gc->chip_types[0].handler		= handle_edge_irq;
	gc->chip_types[0].regs.ack		= PDC_IRQ_CLEAR;
	gc->chip_types[0].regs.mask		= PDC_IRQ_ENABLE;
	gc->chip_types[0].chip.irq_ack		= irq_gc_ack_set_bit;
	gc->chip_types[0].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[0].chip.irq_set_type	= syswake_irq_set_type;
	gc->chip_types[0].chip.irq_set_wake	= pdc_irq_set_wake;
	/* for standby we pass on to the shared syswake IRQ */
	gc->chip_types[0].chip.flags		= IRQCHIP_MASK_ON_SUSPEND;

	/* level interrupts */
	gc->chip_types[1].type			= IRQ_TYPE_LEVEL_MASK;
	gc->chip_types[1].handler		= handle_level_irq;
	gc->chip_types[1].regs.ack		= PDC_IRQ_CLEAR;
	gc->chip_types[1].regs.mask		= PDC_IRQ_ENABLE;
	gc->chip_types[1].chip.irq_ack		= irq_gc_ack_set_bit;
	gc->chip_types[1].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[1].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[1].chip.irq_set_type	= syswake_irq_set_type;
	gc->chip_types[1].chip.irq_set_wake	= pdc_irq_set_wake;
	/* for standby we pass on to the shared syswake IRQ */
	gc->chip_types[1].chip.flags		= IRQCHIP_MASK_ON_SUSPEND;

	/* Set up the hardware to enable interrupt routing */
	pdc_intc_setup(priv);

	/* Setup chained handlers for the peripheral IRQs */
	for (i = 0; i < priv->nr_perips; ++i) {
		irq = priv->perip_irqs[i];
		irq_set_chained_handler_and_data(irq, pdc_intc_perip_isr,
						 priv);
	}

	/* Setup chained handler for the syswake IRQ */
	irq_set_chained_handler_and_data(priv->syswake_irq,
					 pdc_intc_syswake_isr, priv);

	dev_info(&pdev->dev,
		 "PDC IRQ controller initialised (%u perip IRQs, %u syswake IRQs)\n",
		 priv->nr_perips,
		 priv->nr_syswakes);

	return 0;
err_generic:
	irq_domain_remove(priv->domain);
	return ret;
}