#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  init_valid_mask; } ;
struct gpio_chip {int base; TYPE_2__ irq; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; scalar_t__ ngpio; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_startup; } ;
struct chv_pinctrl {TYPE_3__ irqchip; int /*<<< orphan*/  dev; scalar_t__ regs; struct chv_community* community; struct gpio_chip chip; } ;
struct chv_gpio_pinrange {scalar_t__ npins; int /*<<< orphan*/  base; } ;
struct chv_community {int npins; int ngpio_ranges; struct chv_gpio_pinrange* gpio_ranges; int /*<<< orphan*/  nirqs; TYPE_1__* pins; } ;
struct TYPE_5__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ CHV_INTMASK ; 
 scalar_t__ CHV_INTSTAT ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQCHIP_SKIP_SET_WAKE ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct gpio_chip chv_gpio_chip ; 
 int /*<<< orphan*/  chv_gpio_irq_ack ; 
 int /*<<< orphan*/  chv_gpio_irq_handler ; 
 int /*<<< orphan*/  chv_gpio_irq_mask ; 
 int /*<<< orphan*/  chv_gpio_irq_startup ; 
 int /*<<< orphan*/  chv_gpio_irq_type ; 
 int /*<<< orphan*/  chv_gpio_irq_unmask ; 
 int /*<<< orphan*/  chv_init_irq_valid_mask ; 
 int /*<<< orphan*/  chv_no_valid_mask ; 
 int /*<<< orphan*/  chv_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,struct gpio_chip*,struct chv_pinctrl*) ; 
 int devm_irq_alloc_descs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int gpiochip_add_pin_range (struct gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  irq_domain_associate_many (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int chv_gpio_probe(struct chv_pinctrl *pctrl, int irq)
{
	const struct chv_gpio_pinrange *range;
	struct gpio_chip *chip = &pctrl->chip;
	bool need_valid_mask = !dmi_check_system(chv_no_valid_mask);
	const struct chv_community *community = pctrl->community;
	int ret, i, irq_base;

	*chip = chv_gpio_chip;

	chip->ngpio = community->pins[community->npins - 1].number + 1;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->base = -1;
	if (need_valid_mask)
		chip->irq.init_valid_mask = chv_init_irq_valid_mask;

	ret = devm_gpiochip_add_data(pctrl->dev, chip, pctrl);
	if (ret) {
		dev_err(pctrl->dev, "Failed to register gpiochip\n");
		return ret;
	}

	for (i = 0; i < community->ngpio_ranges; i++) {
		range = &community->gpio_ranges[i];
		ret = gpiochip_add_pin_range(chip, dev_name(pctrl->dev),
					     range->base, range->base,
					     range->npins);
		if (ret) {
			dev_err(pctrl->dev, "failed to add GPIO pin range\n");
			return ret;
		}
	}

	/*
	 * The same set of machines in chv_no_valid_mask[] have incorrectly
	 * configured GPIOs that generate spurious interrupts so we use
	 * this same list to apply another quirk for them.
	 *
	 * See also https://bugzilla.kernel.org/show_bug.cgi?id=197953.
	 */
	if (!need_valid_mask) {
		/*
		 * Mask all interrupts the community is able to generate
		 * but leave the ones that can only generate GPEs unmasked.
		 */
		chv_writel(GENMASK(31, pctrl->community->nirqs),
			   pctrl->regs + CHV_INTMASK);
	}

	/* Clear all interrupts */
	chv_writel(0xffff, pctrl->regs + CHV_INTSTAT);

	if (!need_valid_mask) {
		irq_base = devm_irq_alloc_descs(pctrl->dev, -1, 0,
						community->npins, NUMA_NO_NODE);
		if (irq_base < 0) {
			dev_err(pctrl->dev, "Failed to allocate IRQ numbers\n");
			return irq_base;
		}
	}

	pctrl->irqchip.name = "chv-gpio";
	pctrl->irqchip.irq_startup = chv_gpio_irq_startup;
	pctrl->irqchip.irq_ack = chv_gpio_irq_ack;
	pctrl->irqchip.irq_mask = chv_gpio_irq_mask;
	pctrl->irqchip.irq_unmask = chv_gpio_irq_unmask;
	pctrl->irqchip.irq_set_type = chv_gpio_irq_type;
	pctrl->irqchip.flags = IRQCHIP_SKIP_SET_WAKE;

	ret = gpiochip_irqchip_add(chip, &pctrl->irqchip, 0,
				   handle_bad_irq, IRQ_TYPE_NONE);
	if (ret) {
		dev_err(pctrl->dev, "failed to add IRQ chip\n");
		return ret;
	}

	if (!need_valid_mask) {
		for (i = 0; i < community->ngpio_ranges; i++) {
			range = &community->gpio_ranges[i];

			irq_domain_associate_many(chip->irq.domain, irq_base,
						  range->base, range->npins);
			irq_base += range->npins;
		}
	}

	gpiochip_set_chained_irqchip(chip, &pctrl->irqchip, irq,
				     chv_gpio_irq_handler);
	return 0;
}