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
struct atl2_hw {int dummy; } ;
struct atl2_adapter {struct atl2_hw hw; TYPE_2__* netdev; int /*<<< orphan*/  reset_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  tx_carrier_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int ATL2_READ_REG (struct atl2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_FLUSH (struct atl2_hw*) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISR_DIS_INT ; 
 int ISR_DMAR_TO_RST ; 
 int ISR_DMAW_TO_RST ; 
 int ISR_MANUAL ; 
 int ISR_PHY ; 
 int ISR_PHY_LINKDOWN ; 
 int ISR_RX_EVENT ; 
 int ISR_TX_EVENT ; 
 int /*<<< orphan*/  REG_IMR ; 
 int /*<<< orphan*/  REG_ISR ; 
 int /*<<< orphan*/  atl2_check_for_link (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_clear_phy_int (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_intr_rx (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_intr_tx (struct atl2_adapter*) ; 
 struct atl2_adapter* netdev_priv (void*) ; 
 scalar_t__ netif_running (TYPE_2__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t atl2_intr(int irq, void *data)
{
	struct atl2_adapter *adapter = netdev_priv(data);
	struct atl2_hw *hw = &adapter->hw;
	u32 status;

	status = ATL2_READ_REG(hw, REG_ISR);
	if (0 == status)
		return IRQ_NONE;

	/* link event */
	if (status & ISR_PHY)
		atl2_clear_phy_int(adapter);

	/* clear ISR status, and Enable CMB DMA/Disable Interrupt */
	ATL2_WRITE_REG(hw, REG_ISR, status | ISR_DIS_INT);

	/* check if PCIE PHY Link down */
	if (status & ISR_PHY_LINKDOWN) {
		if (netif_running(adapter->netdev)) { /* reset MAC */
			ATL2_WRITE_REG(hw, REG_ISR, 0);
			ATL2_WRITE_REG(hw, REG_IMR, 0);
			ATL2_WRITE_FLUSH(hw);
			schedule_work(&adapter->reset_task);
			return IRQ_HANDLED;
		}
	}

	/* check if DMA read/write error? */
	if (status & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) {
		ATL2_WRITE_REG(hw, REG_ISR, 0);
		ATL2_WRITE_REG(hw, REG_IMR, 0);
		ATL2_WRITE_FLUSH(hw);
		schedule_work(&adapter->reset_task);
		return IRQ_HANDLED;
	}

	/* link event */
	if (status & (ISR_PHY | ISR_MANUAL)) {
		adapter->netdev->stats.tx_carrier_errors++;
		atl2_check_for_link(adapter);
	}

	/* transmit event */
	if (status & ISR_TX_EVENT)
		atl2_intr_tx(adapter);

	/* rx exception */
	if (status & ISR_RX_EVENT)
		atl2_intr_rx(adapter);

	/* re-enable Interrupt */
	ATL2_WRITE_REG(&adapter->hw, REG_ISR, 0);
	return IRQ_HANDLED;
}