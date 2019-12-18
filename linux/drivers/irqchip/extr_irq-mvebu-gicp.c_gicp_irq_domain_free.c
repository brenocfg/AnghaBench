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
struct mvebu_gicp {scalar_t__ spi_cnt; int /*<<< orphan*/  spi_lock; int /*<<< orphan*/  spi_bitmap; int /*<<< orphan*/  dev; } ;
struct irq_domain {struct mvebu_gicp* host_data; } ;
struct irq_data {scalar_t__ hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gicp_irq_domain_free(struct irq_domain *domain,
				 unsigned int virq, unsigned int nr_irqs)
{
	struct mvebu_gicp *gicp = domain->host_data;
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);

	if (d->hwirq >= gicp->spi_cnt) {
		dev_err(gicp->dev, "Invalid hwirq %lu\n", d->hwirq);
		return;
	}

	irq_domain_free_irqs_parent(domain, virq, nr_irqs);

	spin_lock(&gicp->spi_lock);
	__clear_bit(d->hwirq, gicp->spi_bitmap);
	spin_unlock(&gicp->spi_lock);
}