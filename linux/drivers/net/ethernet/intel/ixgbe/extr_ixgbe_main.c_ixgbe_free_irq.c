#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_6__ {int /*<<< orphan*/  ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  ring; } ;
struct ixgbe_q_vector {int flags; int num_q_vectors; struct msix_entry* msix_entries; TYPE_3__ tx; TYPE_2__ rx; struct ixgbe_q_vector** q_vector; TYPE_1__* pdev; } ;
struct ixgbe_adapter {int flags; int num_q_vectors; struct msix_entry* msix_entries; TYPE_3__ tx; TYPE_2__ rx; struct ixgbe_adapter** q_vector; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IXGBE_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ixgbe_q_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_free_irq(struct ixgbe_adapter *adapter)
{
	int vector;

	if (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED)) {
		free_irq(adapter->pdev->irq, adapter);
		return;
	}

	if (!adapter->msix_entries)
		return;

	for (vector = 0; vector < adapter->num_q_vectors; vector++) {
		struct ixgbe_q_vector *q_vector = adapter->q_vector[vector];
		struct msix_entry *entry = &adapter->msix_entries[vector];

		/* free only the irqs that were actually requested */
		if (!q_vector->rx.ring && !q_vector->tx.ring)
			continue;

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hint(entry->vector, NULL);

		free_irq(entry->vector, q_vector);
	}

	free_irq(adapter->msix_entries[vector].vector, adapter);
}