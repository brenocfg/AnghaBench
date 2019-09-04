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
typedef  size_t u16 ;
struct ice_vsi {int base_vector; int irqs_ready; int num_q_vectors; TYPE_3__** q_vectors; struct ice_pf* back; } ;
struct ice_pf {TYPE_2__* pdev; TYPE_1__* msix_entries; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ num_ring_rx; scalar_t__ num_ring_tx; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ice_vsi_release_msix (struct ice_vsi*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_vsi_free_irq(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int base = vsi->base_vector;

	if (test_bit(ICE_FLAG_MSIX_ENA, pf->flags)) {
		int i;

		if (!vsi->q_vectors || !vsi->irqs_ready)
			return;

		vsi->irqs_ready = false;
		for (i = 0; i < vsi->num_q_vectors; i++) {
			u16 vector = i + base;
			int irq_num;

			irq_num = pf->msix_entries[vector].vector;

			/* free only the irqs that were actually requested */
			if (!vsi->q_vectors[i] ||
			    !(vsi->q_vectors[i]->num_ring_tx ||
			      vsi->q_vectors[i]->num_ring_rx))
				continue;

			/* clear the affinity notifier in the IRQ descriptor */
			irq_set_affinity_notifier(irq_num, NULL);

			/* clear the affinity_mask in the IRQ descriptor */
			irq_set_affinity_hint(irq_num, NULL);
			synchronize_irq(irq_num);
			devm_free_irq(&pf->pdev->dev, irq_num,
				      vsi->q_vectors[i]);
		}
		ice_vsi_release_msix(vsi);
	}
}