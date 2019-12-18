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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  bgpio_lock; } ;
struct hlwd_gpio {TYPE_1__ gpioc; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ HW_GPIOB_INTMASK ; 
 struct hlwd_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hlwd_gpio_irq_unmask(struct irq_data *data)
{
	struct hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	unsigned long flags;
	u32 mask;

	spin_lock_irqsave(&hlwd->gpioc.bgpio_lock, flags);
	mask = ioread32be(hlwd->regs + HW_GPIOB_INTMASK);
	mask |= BIT(data->hwirq);
	iowrite32be(mask, hlwd->regs + HW_GPIOB_INTMASK);
	spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);
}