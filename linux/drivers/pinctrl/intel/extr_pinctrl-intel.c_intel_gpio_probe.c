#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; void* name; } ;
struct TYPE_7__ {int base; int /*<<< orphan*/  parent; void* label; int /*<<< orphan*/  ngpio; } ;
struct intel_pinctrl {int irq; int ncommunities; TYPE_3__ irqchip; TYPE_1__ chip; int /*<<< orphan*/  dev; struct intel_community* communities; } ;
struct intel_community {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCHIP_MASK_ON_SUSPEND ; 
 int IRQF_NO_THREAD ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dev_name (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,TYPE_1__*,struct intel_pinctrl*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,void*,struct intel_pinctrl*) ; 
 int gpiochip_irqchip_add (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int intel_gpio_add_pin_ranges (struct intel_pinctrl*,struct intel_community*) ; 
 TYPE_1__ intel_gpio_chip ; 
 int /*<<< orphan*/  intel_gpio_irq ; 
 int /*<<< orphan*/  intel_gpio_irq_ack ; 
 int /*<<< orphan*/  intel_gpio_irq_mask ; 
 int /*<<< orphan*/  intel_gpio_irq_type ; 
 int /*<<< orphan*/  intel_gpio_irq_unmask ; 
 int /*<<< orphan*/  intel_gpio_irq_wake ; 
 int /*<<< orphan*/  intel_gpio_ngpio (struct intel_pinctrl*) ; 

__attribute__((used)) static int intel_gpio_probe(struct intel_pinctrl *pctrl, int irq)
{
	int ret, i;

	pctrl->chip = intel_gpio_chip;

	/* Setup GPIO chip */
	pctrl->chip.ngpio = intel_gpio_ngpio(pctrl);
	pctrl->chip.label = dev_name(pctrl->dev);
	pctrl->chip.parent = pctrl->dev;
	pctrl->chip.base = -1;
	pctrl->irq = irq;

	/* Setup IRQ chip */
	pctrl->irqchip.name = dev_name(pctrl->dev);
	pctrl->irqchip.irq_ack = intel_gpio_irq_ack;
	pctrl->irqchip.irq_mask = intel_gpio_irq_mask;
	pctrl->irqchip.irq_unmask = intel_gpio_irq_unmask;
	pctrl->irqchip.irq_set_type = intel_gpio_irq_type;
	pctrl->irqchip.irq_set_wake = intel_gpio_irq_wake;
	pctrl->irqchip.flags = IRQCHIP_MASK_ON_SUSPEND;

	ret = devm_gpiochip_add_data(pctrl->dev, &pctrl->chip, pctrl);
	if (ret) {
		dev_err(pctrl->dev, "failed to register gpiochip\n");
		return ret;
	}

	for (i = 0; i < pctrl->ncommunities; i++) {
		struct intel_community *community = &pctrl->communities[i];

		ret = intel_gpio_add_pin_ranges(pctrl, community);
		if (ret) {
			dev_err(pctrl->dev, "failed to add GPIO pin range\n");
			return ret;
		}
	}

	/*
	 * We need to request the interrupt here (instead of providing chip
	 * to the irq directly) because on some platforms several GPIO
	 * controllers share the same interrupt line.
	 */
	ret = devm_request_irq(pctrl->dev, irq, intel_gpio_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       dev_name(pctrl->dev), pctrl);
	if (ret) {
		dev_err(pctrl->dev, "failed to request interrupt\n");
		return ret;
	}

	ret = gpiochip_irqchip_add(&pctrl->chip, &pctrl->irqchip, 0,
				   handle_bad_irq, IRQ_TYPE_NONE);
	if (ret) {
		dev_err(pctrl->dev, "failed to add irqchip\n");
		return ret;
	}

	gpiochip_set_chained_irqchip(&pctrl->chip, &pctrl->irqchip, irq, NULL);
	return 0;
}