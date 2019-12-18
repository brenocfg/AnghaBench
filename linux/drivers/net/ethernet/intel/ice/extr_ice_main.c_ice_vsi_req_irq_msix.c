#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int num_q_vectors; int base_vector; int irqs_ready; struct ice_q_vector** q_vectors; int /*<<< orphan*/  netdev; int /*<<< orphan*/  irq_handler; struct ice_pf* back; } ;
struct TYPE_10__ {int /*<<< orphan*/  release; int /*<<< orphan*/  notify; } ;
struct TYPE_7__ {scalar_t__ ring; } ;
struct TYPE_6__ {scalar_t__ ring; } ;
struct ice_q_vector {int /*<<< orphan*/  affinity_mask; TYPE_5__ affinity_notify; int /*<<< orphan*/  name; TYPE_2__ tx; TYPE_1__ rx; } ;
struct ice_pf {TYPE_4__* pdev; TYPE_3__* msix_entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int,struct ice_q_vector**) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ice_q_vector*) ; 
 int /*<<< orphan*/  ice_irq_affinity_notify ; 
 int /*<<< orphan*/  ice_irq_affinity_release ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int,TYPE_5__*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_req_irq_msix(struct ice_vsi *vsi, char *basename)
{
	int q_vectors = vsi->num_q_vectors;
	struct ice_pf *pf = vsi->back;
	int base = vsi->base_vector;
	int rx_int_idx = 0;
	int tx_int_idx = 0;
	int vector, err;
	int irq_num;

	for (vector = 0; vector < q_vectors; vector++) {
		struct ice_q_vector *q_vector = vsi->q_vectors[vector];

		irq_num = pf->msix_entries[base + vector].vector;

		if (q_vector->tx.ring && q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", basename, "TxRx", rx_int_idx++);
			tx_int_idx++;
		} else if (q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", basename, "rx", rx_int_idx++);
		} else if (q_vector->tx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", basename, "tx", tx_int_idx++);
		} else {
			/* skip this unused q_vector */
			continue;
		}
		err = devm_request_irq(&pf->pdev->dev, irq_num,
				       vsi->irq_handler, 0,
				       q_vector->name, q_vector);
		if (err) {
			netdev_err(vsi->netdev,
				   "MSIX request_irq failed, error: %d\n", err);
			goto free_q_irqs;
		}

		/* register for affinity change notifications */
		q_vector->affinity_notify.notify = ice_irq_affinity_notify;
		q_vector->affinity_notify.release = ice_irq_affinity_release;
		irq_set_affinity_notifier(irq_num, &q_vector->affinity_notify);

		/* assign the mask for this irq */
		irq_set_affinity_hint(irq_num, &q_vector->affinity_mask);
	}

	vsi->irqs_ready = true;
	return 0;

free_q_irqs:
	while (vector) {
		vector--;
		irq_num = pf->msix_entries[base + vector].vector,
		irq_set_affinity_notifier(irq_num, NULL);
		irq_set_affinity_hint(irq_num, NULL);
		devm_free_irq(&pf->pdev->dev, irq_num, &vsi->q_vectors[vector]);
	}
	return err;
}