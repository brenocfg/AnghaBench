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
struct megasas_instance {int /*<<< orphan*/  msix_vectors; int /*<<< orphan*/  low_latency_index_start; int /*<<< orphan*/  pdev; scalar_t__ smp_affinity_enable; } ;
struct irq_affinity {int /*<<< orphan*/  pre_vectors; } ;

/* Variables and functions */
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSIX ; 
 int pci_alloc_irq_vectors_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct irq_affinity*) ; 

__attribute__((used)) static int
__megasas_alloc_irq_vectors(struct megasas_instance *instance)
{
	int i, irq_flags;
	struct irq_affinity desc = { .pre_vectors = instance->low_latency_index_start };
	struct irq_affinity *descp = &desc;

	irq_flags = PCI_IRQ_MSIX;

	if (instance->smp_affinity_enable)
		irq_flags |= PCI_IRQ_AFFINITY;
	else
		descp = NULL;

	i = pci_alloc_irq_vectors_affinity(instance->pdev,
		instance->low_latency_index_start,
		instance->msix_vectors, irq_flags, descp);

	return i;
}