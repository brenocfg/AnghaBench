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
struct mvebu_gicp {unsigned int spi_cnt; int /*<<< orphan*/  spi_lock; int /*<<< orphan*/  spi_bitmap; int /*<<< orphan*/  dev; } ;
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct mvebu_gicp* host_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ GIC_SPI ; 
 scalar_t__ IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ gicp_idx_to_spi (struct mvebu_gicp*,unsigned int) ; 
 int /*<<< orphan*/  gicp_irq_chip ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned int,int /*<<< orphan*/ *,struct mvebu_gicp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gicp_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				 unsigned int nr_irqs, void *args)
{
	struct mvebu_gicp *gicp = domain->host_data;
	struct irq_fwspec fwspec;
	unsigned int hwirq;
	int ret;

	spin_lock(&gicp->spi_lock);
	hwirq = find_first_zero_bit(gicp->spi_bitmap, gicp->spi_cnt);
	if (hwirq == gicp->spi_cnt) {
		spin_unlock(&gicp->spi_lock);
		return -ENOSPC;
	}
	__set_bit(hwirq, gicp->spi_bitmap);
	spin_unlock(&gicp->spi_lock);

	fwspec.fwnode = domain->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = GIC_SPI;
	fwspec.param[1] = gicp_idx_to_spi(gicp, hwirq) - 32;
	/*
	 * Assume edge rising for now, it will be properly set when
	 * ->set_type() is called
	 */
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	ret = irq_domain_alloc_irqs_parent(domain, virq, 1, &fwspec);
	if (ret) {
		dev_err(gicp->dev, "Cannot allocate parent IRQ\n");
		goto free_hwirq;
	}

	ret = irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					    &gicp_irq_chip, gicp);
	if (ret)
		goto free_irqs_parent;

	return 0;

free_irqs_parent:
	irq_domain_free_irqs_parent(domain, virq, nr_irqs);
free_hwirq:
	spin_lock(&gicp->spi_lock);
	__clear_bit(hwirq, gicp->spi_bitmap);
	spin_unlock(&gicp->spi_lock);
	return ret;
}