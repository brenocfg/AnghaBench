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
struct TYPE_2__ {int /*<<< orphan*/ * bits; } ;
struct ena_irq {TYPE_1__ affinity_hint_mask; int /*<<< orphan*/  vector; int /*<<< orphan*/  data; int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;
struct ena_adapter {int /*<<< orphan*/  netdev; struct ena_irq* irq_tbl; } ;

/* Variables and functions */
 size_t ENA_MGMNT_IRQ_IDX ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  netif_dbg (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_request_mgmnt_irq(struct ena_adapter *adapter)
{
	unsigned long flags = 0;
	struct ena_irq *irq;
	int rc;

	irq = &adapter->irq_tbl[ENA_MGMNT_IRQ_IDX];
	rc = request_irq(irq->vector, irq->handler, flags, irq->name,
			 irq->data);
	if (rc) {
		netif_err(adapter, probe, adapter->netdev,
			  "failed to request admin irq\n");
		return rc;
	}

	netif_dbg(adapter, probe, adapter->netdev,
		  "set affinity hint of mgmnt irq.to 0x%lx (irq vector: %d)\n",
		  irq->affinity_hint_mask.bits[0], irq->vector);

	irq_set_affinity_hint(irq->vector, &irq->affinity_hint_mask);

	return rc;
}