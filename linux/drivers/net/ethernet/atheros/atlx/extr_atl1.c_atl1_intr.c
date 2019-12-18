#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ hw_addr; } ;
struct TYPE_8__ {TYPE_2__* cmb; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_carrier_errors; } ;
struct atl1_adapter {TYPE_5__ hw; TYPE_4__* pdev; TYPE_3__ cmb; TYPE_1__ soft_stats; int /*<<< orphan*/  reset_dev_task; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int int_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISR_CMB_RX ; 
 int ISR_CMB_TX ; 
 int ISR_DIS_DMA ; 
 int ISR_DIS_INT ; 
 int ISR_DIS_SMB ; 
 int ISR_DMAR_TO_RST ; 
 int ISR_DMAW_TO_RST ; 
 int ISR_GPHY ; 
 int ISR_HOST_RFD_UNRUN ; 
 int ISR_HOST_RRD_OV ; 
 int ISR_PHY_LINKDOWN ; 
 int ISR_RFD_UNRUN ; 
 int ISR_RRD_OV ; 
 int ISR_RXF_OV ; 
 int ISR_SMB ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ REG_ISR ; 
 int /*<<< orphan*/  atl1_check_for_link (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_inc_smb (struct atl1_adapter*) ; 
 scalar_t__ atl1_sched_rings_clean (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atlx_clear_phy_int (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atlx_irq_disable (struct atl1_adapter*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct atl1_adapter* netdev_priv (void*) ; 
 scalar_t__ netif_msg_intr (struct atl1_adapter*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t atl1_intr(int irq, void *data)
{
	struct atl1_adapter *adapter = netdev_priv(data);
	u32 status;

	status = adapter->cmb.cmb->int_stats;
	if (!status)
		return IRQ_NONE;

	/* clear CMB interrupt status at once,
	 * but leave rx/tx interrupt status in case it should be dropped
	 * only if rx/tx processing queued. In other case interrupt
	 * can be lost.
	 */
	adapter->cmb.cmb->int_stats = status & (ISR_CMB_TX | ISR_CMB_RX);

	if (status & ISR_GPHY)	/* clear phy status */
		atlx_clear_phy_int(adapter);

	/* clear ISR status, and Enable CMB DMA/Disable Interrupt */
	iowrite32(status | ISR_DIS_INT, adapter->hw.hw_addr + REG_ISR);

	/* check if SMB intr */
	if (status & ISR_SMB)
		atl1_inc_smb(adapter);

	/* check if PCIE PHY Link down */
	if (status & ISR_PHY_LINKDOWN) {
		if (netif_msg_intr(adapter))
			dev_printk(KERN_DEBUG, &adapter->pdev->dev,
				"pcie phy link down %x\n", status);
		if (netif_running(adapter->netdev)) {	/* reset MAC */
			atlx_irq_disable(adapter);
			schedule_work(&adapter->reset_dev_task);
			return IRQ_HANDLED;
		}
	}

	/* check if DMA read/write error ? */
	if (status & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) {
		if (netif_msg_intr(adapter))
			dev_printk(KERN_DEBUG, &adapter->pdev->dev,
				"pcie DMA r/w error (status = 0x%x)\n",
				status);
		atlx_irq_disable(adapter);
		schedule_work(&adapter->reset_dev_task);
		return IRQ_HANDLED;
	}

	/* link event */
	if (status & ISR_GPHY) {
		adapter->soft_stats.tx_carrier_errors++;
		atl1_check_for_link(adapter);
	}

	/* transmit or receive event */
	if (status & (ISR_CMB_TX | ISR_CMB_RX) &&
	    atl1_sched_rings_clean(adapter))
		adapter->cmb.cmb->int_stats = adapter->cmb.cmb->int_stats &
					      ~(ISR_CMB_TX | ISR_CMB_RX);

	/* rx exception */
	if (unlikely(status & (ISR_RXF_OV | ISR_RFD_UNRUN |
		ISR_RRD_OV | ISR_HOST_RFD_UNRUN |
		ISR_HOST_RRD_OV))) {
		if (netif_msg_intr(adapter))
			dev_printk(KERN_DEBUG,
				&adapter->pdev->dev,
				"rx exception, ISR = 0x%x\n",
				status);
		atl1_sched_rings_clean(adapter);
	}

	/* re-enable Interrupt */
	iowrite32(ISR_DIS_SMB | ISR_DIS_DMA, adapter->hw.hw_addr + REG_ISR);
	return IRQ_HANDLED;
}