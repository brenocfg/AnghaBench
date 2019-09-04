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
typedef  int /*<<< orphan*/  u8 ;
struct pl061 {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 scalar_t__ GPIOIBE ; 
 scalar_t__ GPIOIEV ; 
 scalar_t__ GPIOIS ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int PL061_GPIO_NR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct pl061* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pl061_irq_type(struct irq_data *d, unsigned trigger)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct pl061 *pl061 = gpiochip_get_data(gc);
	int offset = irqd_to_hwirq(d);
	unsigned long flags;
	u8 gpiois, gpioibe, gpioiev;
	u8 bit = BIT(offset);

	if (offset < 0 || offset >= PL061_GPIO_NR)
		return -EINVAL;

	if ((trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) &&
	    (trigger & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING)))
	{
		dev_err(gc->parent,
			"trying to configure line %d for both level and edge "
			"detection, choose one!\n",
			offset);
		return -EINVAL;
	}


	raw_spin_lock_irqsave(&pl061->lock, flags);

	gpioiev = readb(pl061->base + GPIOIEV);
	gpiois = readb(pl061->base + GPIOIS);
	gpioibe = readb(pl061->base + GPIOIBE);

	if (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
		bool polarity = trigger & IRQ_TYPE_LEVEL_HIGH;

		/* Disable edge detection */
		gpioibe &= ~bit;
		/* Enable level detection */
		gpiois |= bit;
		/* Select polarity */
		if (polarity)
			gpioiev |= bit;
		else
			gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_level_irq);
		dev_dbg(gc->parent, "line %d: IRQ on %s level\n",
			offset,
			polarity ? "HIGH" : "LOW");
	} else if ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) {
		/* Disable level detection */
		gpiois &= ~bit;
		/* Select both edges, setting this makes GPIOEV be ignored */
		gpioibe |= bit;
		irq_set_handler_locked(d, handle_edge_irq);
		dev_dbg(gc->parent, "line %d: IRQ on both edges\n", offset);
	} else if ((trigger & IRQ_TYPE_EDGE_RISING) ||
		   (trigger & IRQ_TYPE_EDGE_FALLING)) {
		bool rising = trigger & IRQ_TYPE_EDGE_RISING;

		/* Disable level detection */
		gpiois &= ~bit;
		/* Clear detection on both edges */
		gpioibe &= ~bit;
		/* Select edge */
		if (rising)
			gpioiev |= bit;
		else
			gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_edge_irq);
		dev_dbg(gc->parent, "line %d: IRQ on %s edge\n",
			offset,
			rising ? "RISING" : "FALLING");
	} else {
		/* No trigger: disable everything */
		gpiois &= ~bit;
		gpioibe &= ~bit;
		gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_bad_irq);
		dev_warn(gc->parent, "no trigger selected for line %d\n",
			 offset);
	}

	writeb(gpiois, pl061->base + GPIOIS);
	writeb(gpioibe, pl061->base + GPIOIBE);
	writeb(gpioiev, pl061->base + GPIOIEV);

	raw_spin_unlock_irqrestore(&pl061->lock, flags);

	return 0;
}