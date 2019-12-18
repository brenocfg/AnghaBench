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
typedef  int u32 ;
struct irq_domain {int revmap_size; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct TYPE_2__ {struct irq_domain* domain; } ;
struct gpio_chip {TYPE_1__ irq; } ;
struct armada_37xx_pinctrl {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;

/* Variables and functions */
 int GPIO_PER_REG ; 
 scalar_t__ IRQ_EN ; 
 scalar_t__ IRQ_STATUS ; 
 int IRQ_TYPE_EDGE_BOTH ; 
 int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ armada_37xx_edge_both_irq_swap_pol (struct armada_37xx_pinctrl*,int) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct armada_37xx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_find_mapping (struct irq_domain*,int) ; 
 int irq_get_trigger_type (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void armada_37xx_irq_handler(struct irq_desc *desc)
{
	struct gpio_chip *gc = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct armada_37xx_pinctrl *info = gpiochip_get_data(gc);
	struct irq_domain *d = gc->irq.domain;
	int i;

	chained_irq_enter(chip, desc);
	for (i = 0; i <= d->revmap_size / GPIO_PER_REG; i++) {
		u32 status;
		unsigned long flags;

		spin_lock_irqsave(&info->irq_lock, flags);
		status = readl_relaxed(info->base + IRQ_STATUS + 4 * i);
		/* Manage only the interrupt that was enabled */
		status &= readl_relaxed(info->base + IRQ_EN + 4 * i);
		spin_unlock_irqrestore(&info->irq_lock, flags);
		while (status) {
			u32 hwirq = ffs(status) - 1;
			u32 virq = irq_find_mapping(d, hwirq +
						     i * GPIO_PER_REG);
			u32 t = irq_get_trigger_type(virq);

			if ((t & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH) {
				/* Swap polarity (race with GPIO line) */
				if (armada_37xx_edge_both_irq_swap_pol(info,
					hwirq + i * GPIO_PER_REG)) {
					/*
					 * For spurious irq, which gpio level
					 * is not as expected after incoming
					 * edge, just ack the gpio irq.
					 */
					writel(1 << hwirq,
					       info->base +
					       IRQ_STATUS + 4 * i);
					goto update_status;
				}
			}

			generic_handle_irq(virq);

update_status:
			/* Update status in case a new IRQ appears */
			spin_lock_irqsave(&info->irq_lock, flags);
			status = readl_relaxed(info->base +
					       IRQ_STATUS + 4 * i);
			/* Manage only the interrupt that was enabled */
			status &= readl_relaxed(info->base + IRQ_EN + 4 * i);
			spin_unlock_irqrestore(&info->irq_lock, flags);
		}
	}
	chained_irq_exit(chip, desc);
}