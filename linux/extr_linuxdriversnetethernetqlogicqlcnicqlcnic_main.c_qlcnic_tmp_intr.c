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
struct qlcnic_host_sds_ring {struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {int flags; TYPE_1__* ahw; int /*<<< orphan*/  tgt_status_reg; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  diag_cnt; } ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 scalar_t__ qlcnic_clear_legacy_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_enable_sds_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qlcnic_tmp_intr(int irq, void *data)
{
	struct qlcnic_host_sds_ring *sds_ring = data;
	struct qlcnic_adapter *adapter = sds_ring->adapter;

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		goto done;
	else if (adapter->flags & QLCNIC_MSI_ENABLED) {
		writel(0xffffffff, adapter->tgt_status_reg);
		goto done;
	}

	if (qlcnic_clear_legacy_intr(adapter) == IRQ_NONE)
		return IRQ_NONE;

done:
	adapter->ahw->diag_cnt++;
	qlcnic_enable_sds_intr(adapter, sds_ring);
	return IRQ_HANDLED;
}