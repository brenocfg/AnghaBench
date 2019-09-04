#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {scalar_t__ ring; } ;
struct ixgbe_q_vector {int num_q_vectors; char* name; int flags; struct msix_entry* msix_entries; int /*<<< orphan*/  pdev; struct ixgbe_q_vector** q_vector; int /*<<< orphan*/  affinity_mask; TYPE_2__ tx; TYPE_1__ rx; struct net_device* netdev; } ;
struct ixgbe_adapter {int num_q_vectors; char* name; int flags; struct msix_entry* msix_entries; int /*<<< orphan*/  pdev; struct ixgbe_adapter** q_vector; int /*<<< orphan*/  affinity_mask; TYPE_2__ tx; TYPE_1__ rx; struct net_device* netdev; } ;

/* Variables and functions */
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ixgbe_q_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_msix_clean_rings ; 
 int /*<<< orphan*/ * ixgbe_msix_other ; 
 int /*<<< orphan*/  kfree (struct msix_entry*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct ixgbe_q_vector*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_request_msix_irqs(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	unsigned int ri = 0, ti = 0;
	int vector, err;

	for (vector = 0; vector < adapter->num_q_vectors; vector++) {
		struct ixgbe_q_vector *q_vector = adapter->q_vector[vector];
		struct msix_entry *entry = &adapter->msix_entries[vector];

		if (q_vector->tx.ring && q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-TxRx-%u", netdev->name, ri++);
			ti++;
		} else if (q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-rx-%u", netdev->name, ri++);
		} else if (q_vector->tx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-tx-%u", netdev->name, ti++);
		} else {
			/* skip this unused q_vector */
			continue;
		}
		err = request_irq(entry->vector, &ixgbe_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		if (err) {
			e_err(probe, "request_irq failed for MSIX interrupt "
			      "Error: %d\n", err);
			goto free_queue_irqs;
		}
		/* If Flow Director is enabled, set interrupt affinity */
		if (adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) {
			/* assign the mask for this irq */
			irq_set_affinity_hint(entry->vector,
					      &q_vector->affinity_mask);
		}
	}

	err = request_irq(adapter->msix_entries[vector].vector,
			  ixgbe_msix_other, 0, netdev->name, adapter);
	if (err) {
		e_err(probe, "request_irq for msix_other failed: %d\n", err);
		goto free_queue_irqs;
	}

	return 0;

free_queue_irqs:
	while (vector) {
		vector--;
		irq_set_affinity_hint(adapter->msix_entries[vector].vector,
				      NULL);
		free_irq(adapter->msix_entries[vector].vector,
			 adapter->q_vector[vector]);
	}
	adapter->flags &= ~IXGBE_FLAG_MSIX_ENABLED;
	pci_disable_msix(adapter->pdev);
	kfree(adapter->msix_entries);
	adapter->msix_entries = NULL;
	return err;
}