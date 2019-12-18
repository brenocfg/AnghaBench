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
struct ena_adapter {int msix_vecs; TYPE_1__* irq_tbl; int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int ENA_IO_IRQ_FIRST_IDX ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_disable_io_intr_sync(struct ena_adapter *adapter)
{
	int i;

	if (!netif_running(adapter->netdev))
		return;

	for (i = ENA_IO_IRQ_FIRST_IDX; i < adapter->msix_vecs; i++)
		synchronize_irq(adapter->irq_tbl[i].vector);
}