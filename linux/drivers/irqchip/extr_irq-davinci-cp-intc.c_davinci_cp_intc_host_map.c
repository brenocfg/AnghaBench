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
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  davinci_cp_intc_irq_chip ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_cp_intc_host_map(struct irq_domain *h, unsigned int virq,
			  irq_hw_number_t hw)
{
	pr_debug("cp_intc_host_map(%d, 0x%lx)\n", virq, hw);

	irq_set_chip(virq, &davinci_cp_intc_irq_chip);
	irq_set_probe(virq);
	irq_set_handler(virq, handle_edge_irq);

	return 0;
}