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
struct npcm7xx_gpio {scalar_t__ base; int /*<<< orphan*/  gc; } ;
struct irq_data {TYPE_1__* chip; int /*<<< orphan*/  irq; int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_device; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 scalar_t__ NPCM7XX_GP_N_EVBE ; 
 scalar_t__ NPCM7XX_GP_N_EVTYP ; 
 scalar_t__ NPCM7XX_GP_N_POL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct npcm7xx_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npcm_gpio_clr (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  npcm_gpio_set (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 

__attribute__((used)) static int npcmgpio_set_irq_type(struct irq_data *d, unsigned int type)
{
	struct npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	unsigned int gpio = BIT(d->hwirq);

	dev_dbg(d->chip->parent_device, "setirqtype: %u.%u = %u\n", gpio,
		d->irq, type);
	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		dev_dbg(d->chip->parent_device, "edge.rising\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		break;
	case IRQ_TYPE_EDGE_FALLING:
		dev_dbg(d->chip->parent_device, "edge.falling\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		break;
	case IRQ_TYPE_EDGE_BOTH:
		dev_dbg(d->chip->parent_device, "edge.both\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		dev_dbg(d->chip->parent_device, "level.low\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		dev_dbg(d->chip->parent_device, "level.high\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		break;
	default:
		dev_dbg(d->chip->parent_device, "invalid irq type\n");
		return -EINVAL;
	}

	if (type & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		irq_set_handler_locked(d, handle_level_irq);
	} else if (type & (IRQ_TYPE_EDGE_BOTH | IRQ_TYPE_EDGE_RISING
			   | IRQ_TYPE_EDGE_FALLING)) {
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		irq_set_handler_locked(d, handle_edge_irq);
	}

	return 0;
}