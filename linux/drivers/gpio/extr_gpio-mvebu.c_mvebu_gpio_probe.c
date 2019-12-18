#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_11__ {int base; unsigned int ngpio; int can_sleep; int /*<<< orphan*/  label; int /*<<< orphan*/  dbg_show; struct device_node* of_node; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; TYPE_2__* parent; } ;
struct mvebu_gpio_chip {int soc_variant; int /*<<< orphan*/  domain; TYPE_5__ chip; int /*<<< orphan*/  percpu_regs; int /*<<< orphan*/  regs; scalar_t__ offset; int /*<<< orphan*/  clk; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; void* irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct irq_chip_type {int type; TYPE_1__ chip; int /*<<< orphan*/  handler; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; struct mvebu_gpio_chip* private; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CONFIG_PWM ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO_EDGE_CAUSE_ARMADAXP_OFF (int) ; 
 scalar_t__ GPIO_EDGE_CAUSE_OFF ; 
 scalar_t__ GPIO_EDGE_MASK_ARMADAXP_OFF (int) ; 
 scalar_t__ GPIO_EDGE_MASK_MV78200_OFF (int) ; 
 scalar_t__ GPIO_EDGE_MASK_OFF ; 
 scalar_t__ GPIO_LEVEL_MASK_ARMADAXP_OFF (int) ; 
 scalar_t__ GPIO_LEVEL_MASK_MV78200_OFF (int) ; 
 scalar_t__ GPIO_LEVEL_MASK_OFF ; 
 int IRQ_LEVEL ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int IRQ_TYPE_EDGE_FALLING ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int IRQ_TYPE_LEVEL_LOW ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MVEBU_GPIO_SOC_VARIANT_A8K 131 
#define  MVEBU_GPIO_SOC_VARIANT_ARMADAXP 130 
#define  MVEBU_GPIO_SOC_VARIANT_MV78200 129 
#define  MVEBU_GPIO_SOC_VARIANT_ORION 128 
 int MVEBU_MAX_GPIO_PER_BANK ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_gpiochip_add_data (TYPE_2__*,TYPE_5__*,struct mvebu_gpio_chip*) ; 
 struct mvebu_gpio_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_alloc_domain_generic_chips (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_generic_chip_ops ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct mvebu_gpio_chip*) ; 
 int /*<<< orphan*/  mvebu_gpio_dbg_show ; 
 int /*<<< orphan*/  mvebu_gpio_direction_input ; 
 int /*<<< orphan*/  mvebu_gpio_direction_output ; 
 int /*<<< orphan*/  mvebu_gpio_edge_irq_mask ; 
 int /*<<< orphan*/  mvebu_gpio_edge_irq_unmask ; 
 int /*<<< orphan*/  mvebu_gpio_get ; 
 int /*<<< orphan*/  mvebu_gpio_get_direction ; 
 int /*<<< orphan*/  mvebu_gpio_irq_ack ; 
 int /*<<< orphan*/  mvebu_gpio_irq_handler ; 
 void* mvebu_gpio_irq_set_type ; 
 int /*<<< orphan*/  mvebu_gpio_level_irq_mask ; 
 int /*<<< orphan*/  mvebu_gpio_level_irq_unmask ; 
 int /*<<< orphan*/  mvebu_gpio_of_match ; 
 int mvebu_gpio_probe_raw (struct platform_device*,struct mvebu_gpio_chip*) ; 
 int mvebu_gpio_probe_syscon (struct platform_device*,struct mvebu_gpio_chip*) ; 
 int /*<<< orphan*/  mvebu_gpio_set ; 
 int /*<<< orphan*/  mvebu_gpio_to_irq ; 
 int mvebu_pwm_probe (struct platform_device*,struct mvebu_gpio_chip*,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_irq_count (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvebu_gpio_chip*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_gpio_probe(struct platform_device *pdev)
{
	struct mvebu_gpio_chip *mvchip;
	const struct of_device_id *match;
	struct device_node *np = pdev->dev.of_node;
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	unsigned int ngpios;
	bool have_irqs;
	int soc_variant;
	int i, cpu, id;
	int err;

	match = of_match_device(mvebu_gpio_of_match, &pdev->dev);
	if (match)
		soc_variant = (unsigned long) match->data;
	else
		soc_variant = MVEBU_GPIO_SOC_VARIANT_ORION;

	/* Some gpio controllers do not provide irq support */
	have_irqs = of_irq_count(np) != 0;

	mvchip = devm_kzalloc(&pdev->dev, sizeof(struct mvebu_gpio_chip),
			      GFP_KERNEL);
	if (!mvchip)
		return -ENOMEM;

	platform_set_drvdata(pdev, mvchip);

	if (of_property_read_u32(pdev->dev.of_node, "ngpios", &ngpios)) {
		dev_err(&pdev->dev, "Missing ngpios OF property\n");
		return -ENODEV;
	}

	id = of_alias_get_id(pdev->dev.of_node, "gpio");
	if (id < 0) {
		dev_err(&pdev->dev, "Couldn't get OF id\n");
		return id;
	}

	mvchip->clk = devm_clk_get(&pdev->dev, NULL);
	/* Not all SoCs require a clock.*/
	if (!IS_ERR(mvchip->clk))
		clk_prepare_enable(mvchip->clk);

	mvchip->soc_variant = soc_variant;
	mvchip->chip.label = dev_name(&pdev->dev);
	mvchip->chip.parent = &pdev->dev;
	mvchip->chip.request = gpiochip_generic_request;
	mvchip->chip.free = gpiochip_generic_free;
	mvchip->chip.get_direction = mvebu_gpio_get_direction;
	mvchip->chip.direction_input = mvebu_gpio_direction_input;
	mvchip->chip.get = mvebu_gpio_get;
	mvchip->chip.direction_output = mvebu_gpio_direction_output;
	mvchip->chip.set = mvebu_gpio_set;
	if (have_irqs)
		mvchip->chip.to_irq = mvebu_gpio_to_irq;
	mvchip->chip.base = id * MVEBU_MAX_GPIO_PER_BANK;
	mvchip->chip.ngpio = ngpios;
	mvchip->chip.can_sleep = false;
	mvchip->chip.of_node = np;
	mvchip->chip.dbg_show = mvebu_gpio_dbg_show;

	if (soc_variant == MVEBU_GPIO_SOC_VARIANT_A8K)
		err = mvebu_gpio_probe_syscon(pdev, mvchip);
	else
		err = mvebu_gpio_probe_raw(pdev, mvchip);

	if (err)
		return err;

	/*
	 * Mask and clear GPIO interrupts.
	 */
	switch (soc_variant) {
	case MVEBU_GPIO_SOC_VARIANT_ORION:
	case MVEBU_GPIO_SOC_VARIANT_A8K:
		regmap_write(mvchip->regs,
			     GPIO_EDGE_CAUSE_OFF + mvchip->offset, 0);
		regmap_write(mvchip->regs,
			     GPIO_EDGE_MASK_OFF + mvchip->offset, 0);
		regmap_write(mvchip->regs,
			     GPIO_LEVEL_MASK_OFF + mvchip->offset, 0);
		break;
	case MVEBU_GPIO_SOC_VARIANT_MV78200:
		regmap_write(mvchip->regs, GPIO_EDGE_CAUSE_OFF, 0);
		for (cpu = 0; cpu < 2; cpu++) {
			regmap_write(mvchip->regs,
				     GPIO_EDGE_MASK_MV78200_OFF(cpu), 0);
			regmap_write(mvchip->regs,
				     GPIO_LEVEL_MASK_MV78200_OFF(cpu), 0);
		}
		break;
	case MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		regmap_write(mvchip->regs, GPIO_EDGE_CAUSE_OFF, 0);
		regmap_write(mvchip->regs, GPIO_EDGE_MASK_OFF, 0);
		regmap_write(mvchip->regs, GPIO_LEVEL_MASK_OFF, 0);
		for (cpu = 0; cpu < 4; cpu++) {
			regmap_write(mvchip->percpu_regs,
				     GPIO_EDGE_CAUSE_ARMADAXP_OFF(cpu), 0);
			regmap_write(mvchip->percpu_regs,
				     GPIO_EDGE_MASK_ARMADAXP_OFF(cpu), 0);
			regmap_write(mvchip->percpu_regs,
				     GPIO_LEVEL_MASK_ARMADAXP_OFF(cpu), 0);
		}
		break;
	default:
		BUG();
	}

	devm_gpiochip_add_data(&pdev->dev, &mvchip->chip, mvchip);

	/* Some gpio controllers do not provide irq support */
	if (!have_irqs)
		return 0;

	mvchip->domain =
	    irq_domain_add_linear(np, ngpios, &irq_generic_chip_ops, NULL);
	if (!mvchip->domain) {
		dev_err(&pdev->dev, "couldn't allocate irq domain %s (DT).\n",
			mvchip->chip.label);
		return -ENODEV;
	}

	err = irq_alloc_domain_generic_chips(
	    mvchip->domain, ngpios, 2, np->name, handle_level_irq,
	    IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_LEVEL, 0, 0);
	if (err) {
		dev_err(&pdev->dev, "couldn't allocate irq chips %s (DT).\n",
			mvchip->chip.label);
		goto err_domain;
	}

	/*
	 * NOTE: The common accessors cannot be used because of the percpu
	 * access to the mask registers
	 */
	gc = irq_get_domain_generic_chip(mvchip->domain, 0);
	gc->private = mvchip;
	ct = &gc->chip_types[0];
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->chip.irq_mask = mvebu_gpio_level_irq_mask;
	ct->chip.irq_unmask = mvebu_gpio_level_irq_unmask;
	ct->chip.irq_set_type = mvebu_gpio_irq_set_type;
	ct->chip.name = mvchip->chip.label;

	ct = &gc->chip_types[1];
	ct->type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	ct->chip.irq_ack = mvebu_gpio_irq_ack;
	ct->chip.irq_mask = mvebu_gpio_edge_irq_mask;
	ct->chip.irq_unmask = mvebu_gpio_edge_irq_unmask;
	ct->chip.irq_set_type = mvebu_gpio_irq_set_type;
	ct->handler = handle_edge_irq;
	ct->chip.name = mvchip->chip.label;

	/*
	 * Setup the interrupt handlers. Each chip can have up to 4
	 * interrupt handlers, with each handler dealing with 8 GPIO
	 * pins.
	 */
	for (i = 0; i < 4; i++) {
		int irq = platform_get_irq(pdev, i);

		if (irq < 0)
			continue;
		irq_set_chained_handler_and_data(irq, mvebu_gpio_irq_handler,
						 mvchip);
	}

	/* Some MVEBU SoCs have simple PWM support for GPIO lines */
	if (IS_ENABLED(CONFIG_PWM))
		return mvebu_pwm_probe(pdev, mvchip, id);

	return 0;

err_domain:
	irq_domain_remove(mvchip->domain);

	return err;
}