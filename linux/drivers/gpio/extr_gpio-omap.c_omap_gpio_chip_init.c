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
struct irq_chip {int /*<<< orphan*/ * irq_set_wake; } ;
struct gpio_irq_chip {int num_parents; int first; int /*<<< orphan*/ * parents; int /*<<< orphan*/  default_type; int /*<<< orphan*/  handler; struct irq_chip* chip; } ;
struct TYPE_7__ {char* label; int base; int /*<<< orphan*/ * parent; struct gpio_irq_chip irq; scalar_t__ ngpio; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  set_config; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get_multiple; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; } ;
struct gpio_bank {scalar_t__ width; scalar_t__ is_mpuio; TYPE_3__ chip; int /*<<< orphan*/  irq; TYPE_1__* regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ wkup_en; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int OMAP_MPUIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_irq_alloc_descs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_bank*) ; 
 int gpiochip_add_data (TYPE_3__*,struct gpio_bank*) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  omap_gpio_free ; 
 int /*<<< orphan*/  omap_gpio_get ; 
 int /*<<< orphan*/  omap_gpio_get_direction ; 
 int /*<<< orphan*/  omap_gpio_get_multiple ; 
 int /*<<< orphan*/  omap_gpio_input ; 
 int /*<<< orphan*/  omap_gpio_irq_handler ; 
 int /*<<< orphan*/  omap_gpio_output ; 
 int /*<<< orphan*/  omap_gpio_request ; 
 int /*<<< orphan*/  omap_gpio_set ; 
 int /*<<< orphan*/  omap_gpio_set_config ; 
 int /*<<< orphan*/  omap_gpio_set_multiple ; 
 TYPE_2__ omap_mpuio_device ; 

__attribute__((used)) static int omap_gpio_chip_init(struct gpio_bank *bank, struct irq_chip *irqc)
{
	struct gpio_irq_chip *irq;
	static int gpio;
	const char *label;
	int irq_base = 0;
	int ret;

	/*
	 * REVISIT eventually switch from OMAP-specific gpio structs
	 * over to the generic ones
	 */
	bank->chip.request = omap_gpio_request;
	bank->chip.free = omap_gpio_free;
	bank->chip.get_direction = omap_gpio_get_direction;
	bank->chip.direction_input = omap_gpio_input;
	bank->chip.get = omap_gpio_get;
	bank->chip.get_multiple = omap_gpio_get_multiple;
	bank->chip.direction_output = omap_gpio_output;
	bank->chip.set_config = omap_gpio_set_config;
	bank->chip.set = omap_gpio_set;
	bank->chip.set_multiple = omap_gpio_set_multiple;
	if (bank->is_mpuio) {
		bank->chip.label = "mpuio";
		if (bank->regs->wkup_en)
			bank->chip.parent = &omap_mpuio_device.dev;
		bank->chip.base = OMAP_MPUIO(0);
	} else {
		label = devm_kasprintf(bank->chip.parent, GFP_KERNEL, "gpio-%d-%d",
				       gpio, gpio + bank->width - 1);
		if (!label)
			return -ENOMEM;
		bank->chip.label = label;
		bank->chip.base = gpio;
	}
	bank->chip.ngpio = bank->width;

#ifdef CONFIG_ARCH_OMAP1
	/*
	 * REVISIT: Once we have OMAP1 supporting SPARSE_IRQ, we can drop
	 * irq_alloc_descs() since a base IRQ offset will no longer be needed.
	 */
	irq_base = devm_irq_alloc_descs(bank->chip.parent,
					-1, 0, bank->width, 0);
	if (irq_base < 0) {
		dev_err(bank->chip.parent, "Couldn't allocate IRQ numbers\n");
		return -ENODEV;
	}
#endif

	/* MPUIO is a bit different, reading IRQ status clears it */
	if (bank->is_mpuio && !bank->regs->wkup_en)
		irqc->irq_set_wake = NULL;

	irq = &bank->chip.irq;
	irq->chip = irqc;
	irq->handler = handle_bad_irq;
	irq->default_type = IRQ_TYPE_NONE;
	irq->num_parents = 1;
	irq->parents = &bank->irq;
	irq->first = irq_base;

	ret = gpiochip_add_data(&bank->chip, bank);
	if (ret) {
		dev_err(bank->chip.parent,
			"Could not register gpio chip %d\n", ret);
		return ret;
	}

	ret = devm_request_irq(bank->chip.parent, bank->irq,
			       omap_gpio_irq_handler,
			       0, dev_name(bank->chip.parent), bank);
	if (ret)
		gpiochip_remove(&bank->chip);

	if (!bank->is_mpuio)
		gpio += bank->width;

	return ret;
}