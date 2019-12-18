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
struct irq_affinity {int /*<<< orphan*/  pre_vectors; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  msix_vector_count; int /*<<< orphan*/  high_iops_queues; int /*<<< orphan*/  pdev; scalar_t__ smp_affinity_enable; } ;

/* Variables and functions */
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct irq_affinity*) ; 

__attribute__((used)) static int
_base_alloc_irq_vectors(struct MPT3SAS_ADAPTER *ioc)
{
	int i, irq_flags = PCI_IRQ_MSIX;
	struct irq_affinity desc = { .pre_vectors = ioc->high_iops_queues };
	struct irq_affinity *descp = &desc;

	if (ioc->smp_affinity_enable)
		irq_flags |= PCI_IRQ_AFFINITY;
	else
		descp = NULL;

	ioc_info(ioc, " %d %d\n", ioc->high_iops_queues,
	    ioc->msix_vector_count);

	i = pci_alloc_irq_vectors_affinity(ioc->pdev,
	    ioc->high_iops_queues,
	    ioc->msix_vector_count, irq_flags, descp);

	return i;
}