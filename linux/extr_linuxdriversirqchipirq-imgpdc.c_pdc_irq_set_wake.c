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
struct pdc_intc_priv {unsigned int irq_route; unsigned int syswake_irq; unsigned int* perip_irqs; int /*<<< orphan*/  lock; } ;
struct irq_data {int hwirq; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_IRQ_ROUTE ; 
 scalar_t__ hwirq_is_syswake (int) ; 
 int /*<<< orphan*/  irq_set_irq_wake (unsigned int,unsigned int) ; 
 struct pdc_intc_priv* irqd_to_priv (struct irq_data*) ; 
 int /*<<< orphan*/  pdc_write (struct pdc_intc_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdc_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct pdc_intc_priv *priv = irqd_to_priv(data);
	irq_hw_number_t hw = data->hwirq;
	unsigned int mask = (1 << 16) << hw;
	unsigned int dst_irq;

	raw_spin_lock(&priv->lock);
	if (on)
		priv->irq_route |= mask;
	else
		priv->irq_route &= ~mask;
	pdc_write(priv, PDC_IRQ_ROUTE, priv->irq_route);
	raw_spin_unlock(&priv->lock);

	/* control the destination IRQ wakeup too for standby mode */
	if (hwirq_is_syswake(hw))
		dst_irq = priv->syswake_irq;
	else
		dst_irq = priv->perip_irqs[hw];
	irq_set_irq_wake(dst_irq, on);

	return 0;
}