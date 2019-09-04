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
struct irq_chip_generic {struct dwapb_gpio* private; } ;
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; } ;
struct dwapb_gpio {TYPE_1__* ports; } ;
struct TYPE_2__ {struct gpio_chip gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_INTEN ; 
 int /*<<< orphan*/  dwapb_read (struct dwapb_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwapb_write (struct dwapb_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dwapb_irq_enable(struct irq_data *d)
{
	struct irq_chip_generic *igc = irq_data_get_irq_chip_data(d);
	struct dwapb_gpio *gpio = igc->private;
	struct gpio_chip *gc = &gpio->ports[0].gc;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	val = dwapb_read(gpio, GPIO_INTEN);
	val |= BIT(d->hwirq);
	dwapb_write(gpio, GPIO_INTEN, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
}