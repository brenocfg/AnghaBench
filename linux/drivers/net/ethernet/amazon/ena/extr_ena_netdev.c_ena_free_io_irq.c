#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ena_irq {int /*<<< orphan*/  data; int /*<<< orphan*/  vector; } ;
struct ena_adapter {int msix_vecs; struct ena_irq* irq_tbl; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int ENA_IO_IRQ_FIRST_IDX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ena_free_io_irq(struct ena_adapter *adapter)
{
	struct ena_irq *irq;
	int i;

#ifdef CONFIG_RFS_ACCEL
	if (adapter->msix_vecs >= 1) {
		free_irq_cpu_rmap(adapter->netdev->rx_cpu_rmap);
		adapter->netdev->rx_cpu_rmap = NULL;
	}
#endif /* CONFIG_RFS_ACCEL */

	for (i = ENA_IO_IRQ_FIRST_IDX; i < adapter->msix_vecs; i++) {
		irq = &adapter->irq_tbl[i];
		irq_set_affinity_hint(irq->vector, NULL);
		free_irq(irq->vector, irq->data);
	}
}