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
struct pdc_intc_priv {int nr_syswakes; int /*<<< orphan*/  domain; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_IRQ_ENABLE ; 
 int /*<<< orphan*/  PDC_IRQ_STATUS ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pdc_read (struct pdc_intc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswake_to_hwirq (unsigned int) ; 

__attribute__((used)) static void pdc_intc_syswake_isr(struct irq_desc *desc)
{
	struct pdc_intc_priv *priv;
	unsigned int syswake, irq_no;
	unsigned int status;

	priv = (struct pdc_intc_priv *)irq_desc_get_handler_data(desc);

	status = pdc_read(priv, PDC_IRQ_STATUS) &
		 pdc_read(priv, PDC_IRQ_ENABLE);
	status &= (1 << priv->nr_syswakes) - 1;

	for (syswake = 0; status; status >>= 1, ++syswake) {
		/* Has this sys_wake triggered? */
		if (!(status & 1))
			continue;

		irq_no = irq_linear_revmap(priv->domain,
					   syswake_to_hwirq(syswake));
		generic_handle_irq(irq_no);
	}
}