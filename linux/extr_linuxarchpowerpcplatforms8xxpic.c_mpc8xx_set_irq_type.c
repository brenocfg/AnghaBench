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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_siel; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 unsigned int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 unsigned int mpc8xx_irqd_to_bit (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* siu_reg ; 

__attribute__((used)) static int mpc8xx_set_irq_type(struct irq_data *d, unsigned int flow_type)
{
	/* only external IRQ senses are programmable */
	if ((flow_type & IRQ_TYPE_EDGE_FALLING) && !(irqd_to_hwirq(d) & 1)) {
		unsigned int siel = in_be32(&siu_reg->sc_siel);
		siel |= mpc8xx_irqd_to_bit(d);
		out_be32(&siu_reg->sc_siel, siel);
		irq_set_handler_locked(d, handle_edge_irq);
	}
	return 0;
}