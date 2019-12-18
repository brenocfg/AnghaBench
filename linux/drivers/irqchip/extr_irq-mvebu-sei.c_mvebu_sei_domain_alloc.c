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
struct mvebu_sei {int dummy; } ;
struct irq_fwspec {int /*<<< orphan*/ * param; } ;
struct irq_domain {struct mvebu_sei* host_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvebu_sei*) ; 
 int /*<<< orphan*/  mvebu_sei_irq_chip ; 

__attribute__((used)) static int mvebu_sei_domain_alloc(struct irq_domain *domain, unsigned int virq,
				  unsigned int nr_irqs, void *arg)
{
	struct mvebu_sei *sei = domain->host_data;
	struct irq_fwspec *fwspec = arg;

	/* Not much to do, just setup the irqdata */
	irq_domain_set_hwirq_and_chip(domain, virq, fwspec->param[0],
				      &mvebu_sei_irq_chip, sei);

	return 0;
}