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
struct irq_domain {int dummy; } ;
struct irq_data {size_t hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  safe_map; int /*<<< orphan*/  (* write ) (size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * irq_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_FREE ; 
 TYPE_1__* cb ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_reset_irq_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crossbar_domain_free(struct irq_domain *domain, unsigned int virq,
				 unsigned int nr_irqs)
{
	int i;

	raw_spin_lock(&cb->lock);
	for (i = 0; i < nr_irqs; i++) {
		struct irq_data *d = irq_domain_get_irq_data(domain, virq + i);

		irq_domain_reset_irq_data(d);
		cb->irq_map[d->hwirq] = IRQ_FREE;
		cb->write(d->hwirq, cb->safe_map);
	}
	raw_spin_unlock(&cb->lock);
}