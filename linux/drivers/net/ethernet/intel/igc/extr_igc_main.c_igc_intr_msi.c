#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct igc_q_vector {int /*<<< orphan*/  napi; } ;
struct TYPE_4__ {int get_link_status; } ;
struct igc_hw {TYPE_2__ mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  doosync; } ;
struct igc_adapter {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; TYPE_1__ stats; int /*<<< orphan*/  reset_task; struct igc_hw hw; struct igc_q_vector** q_vector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ICR ; 
 int IGC_ICR_DOUTSYNC ; 
 int IGC_ICR_DRSTA ; 
 int IGC_ICR_LSC ; 
 int IGC_ICR_RXSEQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __IGC_DOWN ; 
 int /*<<< orphan*/  igc_write_itr (struct igc_q_vector*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t igc_intr_msi(int irq, void *data)
{
	struct igc_adapter *adapter = data;
	struct igc_q_vector *q_vector = adapter->q_vector[0];
	struct igc_hw *hw = &adapter->hw;
	/* read ICR disables interrupts using IAM */
	u32 icr = rd32(IGC_ICR);

	igc_write_itr(q_vector);

	if (icr & IGC_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	if (icr & IGC_ICR_DOUTSYNC) {
		/* HW is reporting DMA is out of sync */
		adapter->stats.doosync++;
	}

	if (icr & (IGC_ICR_RXSEQ | IGC_ICR_LSC)) {
		hw->mac.get_link_status = 1;
		if (!test_bit(__IGC_DOWN, &adapter->state))
			mod_timer(&adapter->watchdog_timer, jiffies + 1);
	}

	napi_schedule(&q_vector->napi);

	return IRQ_HANDLED;
}