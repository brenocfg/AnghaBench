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
struct spmi_pmic_arb {TYPE_1__* spmic; } ;
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct spmi_pmic_arb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmic_arb_irqchip ; 

__attribute__((used)) static void qpnpint_irq_domain_map(struct spmi_pmic_arb *pmic_arb,
				   struct irq_domain *domain, unsigned int virq,
				   irq_hw_number_t hwirq, unsigned int type)
{
	irq_flow_handler_t handler;

	dev_dbg(&pmic_arb->spmic->dev, "virq = %u, hwirq = %lu, type = %u\n",
		virq, hwirq, type);

	if (type & IRQ_TYPE_EDGE_BOTH)
		handler = handle_edge_irq;
	else
		handler = handle_level_irq;

	irq_domain_set_info(domain, virq, hwirq, &pmic_arb_irqchip, pmic_arb,
			    handler, NULL, NULL);
}