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
struct i40e_vsi {int num_q_vectors; int base_vector; int irqs_ready; struct i40e_q_vector** q_vectors; int /*<<< orphan*/  irq_handler; struct i40e_pf* back; } ;
struct TYPE_10__ {int /*<<< orphan*/  release; int /*<<< orphan*/  notify; } ;
struct TYPE_7__ {scalar_t__ ring; } ;
struct TYPE_6__ {scalar_t__ ring; } ;
struct i40e_q_vector {int /*<<< orphan*/  v_idx; TYPE_5__ affinity_notify; int /*<<< orphan*/  name; TYPE_2__ tx; TYPE_1__ rx; } ;
struct i40e_pf {TYPE_4__* msix_entries; TYPE_3__* pdev; } ;
struct TYPE_9__ {int vector; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int cpumask_local_spread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct i40e_q_vector**) ; 
 int /*<<< orphan*/ * get_cpu_mask (int) ; 
 int /*<<< orphan*/  i40e_irq_affinity_notify ; 
 int /*<<< orphan*/  i40e_irq_affinity_release ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int,TYPE_5__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40e_q_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_vsi_request_irq_msix(struct i40e_vsi *vsi, char *basename)
{
	int q_vectors = vsi->num_q_vectors;
	struct i40e_pf *pf = vsi->back;
	int base = vsi->base_vector;
	int rx_int_idx = 0;
	int tx_int_idx = 0;
	int vector, err;
	int irq_num;
	int cpu;

	for (vector = 0; vector < q_vectors; vector++) {
		struct i40e_q_vector *q_vector = vsi->q_vectors[vector];

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
		err = request_irq(irq_num,
				  vsi->irq_handler,
				  0,
				  q_vector->name,
				  q_vector);
		if (err) {
			dev_info(&pf->pdev->dev,
				 "MSIX request_irq failed, error: %d\n", err);
			goto free_queue_irqs;
		}

		/* register for affinity change notifications */
		q_vector->affinity_notify.notify = i40e_irq_affinity_notify;
		q_vector->affinity_notify.release = i40e_irq_affinity_release;
		irq_set_affinity_notifier(irq_num, &q_vector->affinity_notify);
		/* Spread affinity hints out across online CPUs.
		 *
		 * get_cpu_mask returns a static constant mask with
		 * a permanent lifetime so it's ok to pass to
		 * irq_set_affinity_hint without making a copy.
		 */
		cpu = cpumask_local_spread(q_vector->v_idx, -1);
		irq_set_affinity_hint(irq_num, get_cpu_mask(cpu));
	}

	vsi->irqs_ready = true;
	return 0;

free_queue_irqs:
	while (vector) {
		vector--;
		irq_num = pf->msix_entries[base + vector].vector;
		irq_set_affinity_notifier(irq_num, NULL);
		irq_set_affinity_hint(irq_num, NULL);
		free_irq(irq_num, &vsi->q_vectors[vector]);
	}
	return err;
}