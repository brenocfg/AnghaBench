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
struct pdc_intc_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_route; } ;
struct irq_data {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_IRQ_ROUTE ; 
 struct pdc_intc_priv* irqd_to_priv (struct irq_data*) ; 
 int /*<<< orphan*/  pdc_write (struct pdc_intc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perip_irq_mask(struct irq_data *data)
{
	struct pdc_intc_priv *priv = irqd_to_priv(data);

	raw_spin_lock(&priv->lock);
	priv->irq_route &= ~data->mask;
	pdc_write(priv, PDC_IRQ_ROUTE, priv->irq_route);
	raw_spin_unlock(&priv->lock);
}