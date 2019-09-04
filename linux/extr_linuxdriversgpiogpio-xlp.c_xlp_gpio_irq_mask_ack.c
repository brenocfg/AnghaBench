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
struct xlp_gpio_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_enabled_mask; int /*<<< orphan*/  gpio_intr_stat; int /*<<< orphan*/  gpio_intr_en; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xlp_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xlp_gpio_set_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlp_gpio_irq_mask_ack(struct irq_data *d)
{
	struct gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	struct xlp_gpio_priv *priv = gpiochip_get_data(gc);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	xlp_gpio_set_reg(priv->gpio_intr_en, d->hwirq, 0x0);
	xlp_gpio_set_reg(priv->gpio_intr_stat, d->hwirq, 0x1);
	__clear_bit(d->hwirq, priv->gpio_enabled_mask);
	spin_unlock_irqrestore(&priv->lock, flags);
}