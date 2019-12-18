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
typedef  scalar_t__ u32 ;
struct ena_adapter {scalar_t__ num_queues; TYPE_1__* netdev; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int ENA_IO_IRQ_IDX (scalar_t__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * alloc_irq_cpu_rmap (scalar_t__) ; 
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 
 int irq_cpu_rmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ena_init_rx_cpu_rmap(struct ena_adapter *adapter)
{
#ifdef CONFIG_RFS_ACCEL
	u32 i;
	int rc;

	adapter->netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(adapter->num_queues);
	if (!adapter->netdev->rx_cpu_rmap)
		return -ENOMEM;
	for (i = 0; i < adapter->num_queues; i++) {
		int irq_idx = ENA_IO_IRQ_IDX(i);

		rc = irq_cpu_rmap_add(adapter->netdev->rx_cpu_rmap,
				      pci_irq_vector(adapter->pdev, irq_idx));
		if (rc) {
			free_irq_cpu_rmap(adapter->netdev->rx_cpu_rmap);
			adapter->netdev->rx_cpu_rmap = NULL;
			return rc;
		}
	}
#endif /* CONFIG_RFS_ACCEL */
	return 0;
}