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
struct TYPE_10__ {int /*<<< orphan*/  release; int /*<<< orphan*/  notify; } ;
struct TYPE_7__ {scalar_t__ ring; } ;
struct TYPE_6__ {scalar_t__ ring; } ;
struct iavf_q_vector {int /*<<< orphan*/  v_idx; TYPE_5__ affinity_notify; int /*<<< orphan*/  name; TYPE_2__ tx; TYPE_1__ rx; } ;
struct iavf_adapter {unsigned int num_msix_vectors; struct iavf_q_vector* q_vectors; TYPE_4__* msix_entries; TYPE_3__* pdev; } ;
struct TYPE_9__ {int vector; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int NONQ_VECS ; 
 int cpumask_local_spread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct iavf_q_vector*) ; 
 int /*<<< orphan*/ * get_cpu_mask (int) ; 
 int /*<<< orphan*/  iavf_irq_affinity_notify ; 
 int /*<<< orphan*/  iavf_irq_affinity_release ; 
 int /*<<< orphan*/  iavf_irq_disable (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_msix_clean_rings ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int,TYPE_5__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iavf_q_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_request_traffic_irqs(struct iavf_adapter *adapter, char *basename)
{
	unsigned int vector, q_vectors;
	unsigned int rx_int_idx = 0, tx_int_idx = 0;
	int irq_num, err;
	int cpu;

	iavf_irq_disable(adapter);
	/* Decrement for Other and TCP Timer vectors */
	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	for (vector = 0; vector < q_vectors; vector++) {
		struct iavf_q_vector *q_vector = &adapter->q_vectors[vector];

		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;

		if (q_vector->tx.ring && q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "iavf-%s-TxRx-%d", basename, rx_int_idx++);
			tx_int_idx++;
		} else if (q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "iavf-%s-rx-%d", basename, rx_int_idx++);
		} else if (q_vector->tx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "iavf-%s-tx-%d", basename, tx_int_idx++);
		} else {
			/* skip this unused q_vector */
			continue;
		}
		err = request_irq(irq_num,
				  iavf_msix_clean_rings,
				  0,
				  q_vector->name,
				  q_vector);
		if (err) {
			dev_info(&adapter->pdev->dev,
				 "Request_irq failed, error: %d\n", err);
			goto free_queue_irqs;
		}
		/* register for affinity change notifications */
		q_vector->affinity_notify.notify = iavf_irq_affinity_notify;
		q_vector->affinity_notify.release =
						   iavf_irq_affinity_release;
		irq_set_affinity_notifier(irq_num, &q_vector->affinity_notify);
		/* Spread the IRQ affinity hints across online CPUs. Note that
		 * get_cpu_mask returns a mask with a permanent lifetime so
		 * it's safe to use as a hint for irq_set_affinity_hint.
		 */
		cpu = cpumask_local_spread(q_vector->v_idx, -1);
		irq_set_affinity_hint(irq_num, get_cpu_mask(cpu));
	}

	return 0;

free_queue_irqs:
	while (vector) {
		vector--;
		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;
		irq_set_affinity_notifier(irq_num, NULL);
		irq_set_affinity_hint(irq_num, NULL);
		free_irq(irq_num, &adapter->q_vectors[vector]);
	}
	return err;
}