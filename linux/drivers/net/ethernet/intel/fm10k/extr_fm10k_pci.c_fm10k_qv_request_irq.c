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
struct net_device {char* name; } ;
struct msix_entry {int /*<<< orphan*/  vector; int /*<<< orphan*/  entry; } ;
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_5__ {scalar_t__ count; } ;
struct fm10k_q_vector {int /*<<< orphan*/ * itr; TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {int num_q_vectors; struct fm10k_q_vector** q_vector; int /*<<< orphan*/ * uc_addr; struct msix_entry* msix_entries; struct fm10k_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 size_t FM10K_ITR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_ITR_ENABLE ; 
 int /*<<< orphan*/  FM10K_ITR_MASK_SET ; 
 size_t FM10K_VFITR (int /*<<< orphan*/ ) ; 
 size_t NON_Q_VECTORS ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_msix_clean_rings ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fm10k_q_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fm10k_q_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fm10k_qv_request_irq(struct fm10k_intfc *interface)
{
	struct net_device *dev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;
	struct msix_entry *entry;
	unsigned int ri = 0, ti = 0;
	int vector, err;

	entry = &interface->msix_entries[NON_Q_VECTORS];

	for (vector = 0; vector < interface->num_q_vectors; vector++) {
		struct fm10k_q_vector *q_vector = interface->q_vector[vector];

		/* name the vector */
		if (q_vector->tx.count && q_vector->rx.count) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-TxRx-%u", dev->name, ri++);
			ti++;
		} else if (q_vector->rx.count) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-rx-%u", dev->name, ri++);
		} else if (q_vector->tx.count) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "%s-tx-%u", dev->name, ti++);
		} else {
			/* skip this unused q_vector */
			continue;
		}

		/* Assign ITR register to q_vector */
		q_vector->itr = (hw->mac.type == fm10k_mac_pf) ?
				&interface->uc_addr[FM10K_ITR(entry->entry)] :
				&interface->uc_addr[FM10K_VFITR(entry->entry)];

		/* request the IRQ */
		err = request_irq(entry->vector, &fm10k_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		if (err) {
			netif_err(interface, probe, dev,
				  "request_irq failed for MSIX interrupt Error: %d\n",
				  err);
			goto err_out;
		}

		/* assign the mask for this irq */
		irq_set_affinity_hint(entry->vector, &q_vector->affinity_mask);

		/* Enable q_vector */
		writel(FM10K_ITR_ENABLE, q_vector->itr);

		entry++;
	}

	return 0;

err_out:
	/* wind through the ring freeing all entries and vectors */
	while (vector) {
		struct fm10k_q_vector *q_vector;

		entry--;
		vector--;
		q_vector = interface->q_vector[vector];

		if (!q_vector->tx.count && !q_vector->rx.count)
			continue;

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hint(entry->vector, NULL);

		/* disable interrupts */
		writel(FM10K_ITR_MASK_SET, q_vector->itr);

		free_irq(entry->vector, q_vector);
	}

	return err;
}