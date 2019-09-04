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
struct pdc_intc_priv {unsigned int nr_perips; unsigned int* perip_irqs; int /*<<< orphan*/  domain; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void pdc_intc_perip_isr(struct irq_desc *desc)
{
	unsigned int irq = irq_desc_get_irq(desc);
	struct pdc_intc_priv *priv;
	unsigned int i, irq_no;

	priv = (struct pdc_intc_priv *)irq_desc_get_handler_data(desc);

	/* find the peripheral number */
	for (i = 0; i < priv->nr_perips; ++i)
		if (irq == priv->perip_irqs[i])
			goto found;

	/* should never get here */
	return;
found:

	/* pass on the interrupt */
	irq_no = irq_linear_revmap(priv->domain, i);
	generic_handle_irq(irq_no);
}