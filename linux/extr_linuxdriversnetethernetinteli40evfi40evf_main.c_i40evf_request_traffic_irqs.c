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
struct i40evf_adapter {unsigned int num_msix_vectors; struct i40e_q_vector* q_vectors; TYPE_4__* msix_entries; TYPE_3__* pdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  release; int /*<<< orphan*/  notify; } ;
struct TYPE_7__ {scalar_t__ ring; } ;
struct TYPE_6__ {scalar_t__ ring; } ;
struct i40e_q_vector {int /*<<< orphan*/  v_idx; TYPE_5__ affinity_notify; int /*<<< orphan*/  name; TYPE_2__ tx; TYPE_1__ rx; } ;
struct TYPE_9__ {int vector; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int NONQ_VECS ; 
 int cpumask_local_spread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct i40e_q_vector*) ; 
 int /*<<< orphan*/ * get_cpu_mask (int) ; 
 int /*<<< orphan*/  i40evf_irq_affinity_notify ; 
 int /*<<< orphan*/  i40evf_irq_affinity_release ; 
 int /*<<< orphan*/  i40evf_irq_disable (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_msix_clean_rings ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int,TYPE_5__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40e_q_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i40evf_request_traffic_irqs(struct i40evf_adapter *adapter, char *basename)
{
	unsigned int vector, q_vectors;
	unsigned int rx_int_idx = 0, tx_int_idx = 0;
	int irq_num, err;
	int cpu;

	i40evf_irq_disable(adapter);
	/* Decrement for Other and TCP Timer vectors */
	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	for (vector = 0; vector < q_vectors; vector++) {
		struct i40e_q_vector *q_vector = &adapter->q_vectors[vector];
		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;

		if (q_vector->tx.ring && q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "i40evf-%s-TxRx-%d", basename, rx_int_idx++);
			tx_int_idx++;
		} else if (q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "i40evf-%s-rx-%d", basename, rx_int_idx++);
		} else if (q_vector->tx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name),
				 "i40evf-%s-tx-%d", basename, tx_int_idx++);
		} else {
			/* skip this unused q_vector */
			continue;
		}
		err = request_irq(irq_num,
				  i40evf_msix_clean_rings,
				  0,
				  q_vector->name,
				  q_vector);
		if (err) {
			dev_info(&adapter->pdev->dev,
				 "Request_irq failed, error: %d\n", err);
			goto free_queue_irqs;
		}
		/* register for affinity change notifications */
		q_vector->affinity_notify.notify = i40evf_irq_affinity_notify;
		q_vector->affinity_notify.release =
						   i40evf_irq_affinity_release;
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