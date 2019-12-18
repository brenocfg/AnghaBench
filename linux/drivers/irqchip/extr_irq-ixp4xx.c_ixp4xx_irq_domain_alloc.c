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
struct ixp4xx_irq {int /*<<< orphan*/  irqchip; } ;
struct irq_fwspec {int dummy; } ;
struct irq_domain {struct ixp4xx_irq* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 unsigned int IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,struct ixp4xx_irq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int ixp4xx_irq_domain_translate (struct irq_domain*,struct irq_fwspec*,scalar_t__*,unsigned int*) ; 

__attribute__((used)) static int ixp4xx_irq_domain_alloc(struct irq_domain *d,
				   unsigned int irq, unsigned int nr_irqs,
				   void *data)
{
	struct ixp4xx_irq *ixi = d->host_data;
	irq_hw_number_t hwirq;
	unsigned int type = IRQ_TYPE_NONE;
	struct irq_fwspec *fwspec = data;
	int ret;
	int i;

	ret = ixp4xx_irq_domain_translate(d, fwspec, &hwirq, &type);
	if (ret)
		return ret;

	for (i = 0; i < nr_irqs; i++) {
		/*
		 * TODO: after converting IXP4xx to only device tree, set
		 * handle_bad_irq as default handler and assume all consumers
		 * call .set_type() as this is provided in the second cell in
		 * the device tree phandle.
		 */
		irq_domain_set_info(d,
				    irq + i,
				    hwirq + i,
				    &ixi->irqchip,
				    ixi,
				    handle_level_irq,
				    NULL, NULL);
		irq_set_probe(irq + i);
	}

	return 0;
}