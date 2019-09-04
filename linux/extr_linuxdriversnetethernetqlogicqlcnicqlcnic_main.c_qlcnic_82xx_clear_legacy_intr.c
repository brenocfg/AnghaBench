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
struct qlcnic_adapter {int /*<<< orphan*/  isr_int_vec; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  crb_int_state_reg; TYPE_1__* ahw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int int_vec_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR_LEGACY_INT_TRIGGERED (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qlcnic_82xx_clear_legacy_intr(struct qlcnic_adapter *adapter)
{
	u32 status;

	status = readl(adapter->isr_int_vec);

	if (!(status & adapter->ahw->int_vec_bit))
		return IRQ_NONE;

	/* check interrupt state machine, to be sure */
	status = readl(adapter->crb_int_state_reg);
	if (!ISR_LEGACY_INT_TRIGGERED(status))
		return IRQ_NONE;

	writel(0xffffffff, adapter->tgt_status_reg);
	/* read twice to ensure write is flushed */
	readl(adapter->isr_int_vec);
	readl(adapter->isr_int_vec);

	return IRQ_HANDLED;
}