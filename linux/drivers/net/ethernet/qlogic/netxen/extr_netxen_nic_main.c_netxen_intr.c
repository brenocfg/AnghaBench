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
typedef  int u32 ;
struct nx_host_sds_ring {int /*<<< orphan*/  napi; struct netxen_adapter* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int int_vec_bit; int /*<<< orphan*/  isr_int_vec; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  crb_int_state_reg; scalar_t__ portnum; TYPE_1__ ahw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR_LEGACY_INT_TRIGGERED (int) ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netxen_nic_disable_int (struct nx_host_sds_ring*) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t netxen_intr(int irq, void *data)
{
	struct nx_host_sds_ring *sds_ring = data;
	struct netxen_adapter *adapter = sds_ring->adapter;
	u32 status = 0;

	status = readl(adapter->isr_int_vec);

	if (!(status & adapter->int_vec_bit))
		return IRQ_NONE;

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id)) {
		/* check interrupt state machine, to be sure */
		status = readl(adapter->crb_int_state_reg);
		if (!ISR_LEGACY_INT_TRIGGERED(status))
			return IRQ_NONE;

	} else {
		unsigned long our_int = 0;

		our_int = readl(adapter->crb_int_state_reg);

		/* not our interrupt */
		if (!test_and_clear_bit((7 + adapter->portnum), &our_int))
			return IRQ_NONE;

		/* claim interrupt */
		writel((our_int & 0xffffffff), adapter->crb_int_state_reg);

		/* clear interrupt */
		netxen_nic_disable_int(sds_ring);
	}

	writel(0xffffffff, adapter->tgt_status_reg);
	/* read twice to ensure write is flushed */
	readl(adapter->isr_int_vec);
	readl(adapter->isr_int_vec);

	napi_schedule(&sds_ring->napi);

	return IRQ_HANDLED;
}