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
struct mtk_pcie_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  msi_irq_in_use; } ;
struct irq_domain {struct mtk_pcie_port* host_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned long MTK_MSI_IRQS_NUM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct mtk_pcie_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_msi_bottom_irq_chip ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_pcie_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				     unsigned int nr_irqs, void *args)
{
	struct mtk_pcie_port *port = domain->host_data;
	unsigned long bit;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&port->lock);

	bit = find_first_zero_bit(port->msi_irq_in_use, MTK_MSI_IRQS_NUM);
	if (bit >= MTK_MSI_IRQS_NUM) {
		mutex_unlock(&port->lock);
		return -ENOSPC;
	}

	__set_bit(bit, port->msi_irq_in_use);

	mutex_unlock(&port->lock);

	irq_domain_set_info(domain, virq, bit, &mtk_msi_bottom_irq_chip,
			    domain->host_data, handle_edge_irq,
			    NULL, NULL);

	return 0;
}