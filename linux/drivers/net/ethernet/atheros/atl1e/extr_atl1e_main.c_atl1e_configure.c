#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct atl1e_hw {int max_frame_size; int smb_timer; int /*<<< orphan*/  ict; int /*<<< orphan*/  tx_count_down; int /*<<< orphan*/  rx_count_down; int /*<<< orphan*/  tpd_thresh; int /*<<< orphan*/  rrd_thresh; int /*<<< orphan*/  imt; } ;
struct atl1e_adapter {int /*<<< orphan*/  netdev; struct atl1e_hw hw; } ;

/* Variables and functions */
 int AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AT_WRITE_REGW (struct atl1e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int ISR_PHY_LINKDOWN ; 
 int MASTER_CTRL_ITIMER2_EN ; 
 int MASTER_CTRL_ITIMER_EN ; 
 int MASTER_CTRL_LED_MODE ; 
 int /*<<< orphan*/  REG_CMBDISDMA_TIMER ; 
 int /*<<< orphan*/  REG_IRQ_MODU_TIMER2_INIT ; 
 int /*<<< orphan*/  REG_IRQ_MODU_TIMER_INIT ; 
 int /*<<< orphan*/  REG_ISR ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  REG_MTU ; 
 int /*<<< orphan*/  REG_SMB_STAT_TIMER ; 
 int /*<<< orphan*/  REG_TRIG_RRD_THRESH ; 
 int /*<<< orphan*/  REG_TRIG_RXTIMER ; 
 int /*<<< orphan*/  REG_TRIG_TPD_THRESH ; 
 int /*<<< orphan*/  REG_TRIG_TXTIMER ; 
 int /*<<< orphan*/  REG_WOL_CTRL ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  atl1e_configure_des_ring (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_configure_dma (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_configure_rx (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_configure_tx (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_hw_set_mac_addr (struct atl1e_hw*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1e_configure(struct atl1e_adapter *adapter)
{
	struct atl1e_hw *hw = &adapter->hw;

	u32 intr_status_data = 0;

	/* clear interrupt status */
	AT_WRITE_REG(hw, REG_ISR, ~0);

	/* 1. set MAC Address */
	atl1e_hw_set_mac_addr(hw);

	/* 2. Init the Multicast HASH table done by set_muti */

	/* 3. Clear any WOL status */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/* 4. Descripter Ring BaseMem/Length/Read ptr/Write ptr
	 *    TPD Ring/SMB/RXF0 Page CMBs, they use the same
	 *    High 32bits memory */
	atl1e_configure_des_ring(adapter);

	/* 5. set Interrupt Moderator Timer */
	AT_WRITE_REGW(hw, REG_IRQ_MODU_TIMER_INIT, hw->imt);
	AT_WRITE_REGW(hw, REG_IRQ_MODU_TIMER2_INIT, hw->imt);
	AT_WRITE_REG(hw, REG_MASTER_CTRL, MASTER_CTRL_LED_MODE |
			MASTER_CTRL_ITIMER_EN | MASTER_CTRL_ITIMER2_EN);

	/* 6. rx/tx threshold to trig interrupt */
	AT_WRITE_REGW(hw, REG_TRIG_RRD_THRESH, hw->rrd_thresh);
	AT_WRITE_REGW(hw, REG_TRIG_TPD_THRESH, hw->tpd_thresh);
	AT_WRITE_REGW(hw, REG_TRIG_RXTIMER, hw->rx_count_down);
	AT_WRITE_REGW(hw, REG_TRIG_TXTIMER, hw->tx_count_down);

	/* 7. set Interrupt Clear Timer */
	AT_WRITE_REGW(hw, REG_CMBDISDMA_TIMER, hw->ict);

	/* 8. set MTU */
	AT_WRITE_REG(hw, REG_MTU, hw->max_frame_size + ETH_HLEN +
			VLAN_HLEN + ETH_FCS_LEN);

	/* 9. config TXQ early tx threshold */
	atl1e_configure_tx(adapter);

	/* 10. config RXQ */
	atl1e_configure_rx(adapter);

	/* 11. config  DMA Engine */
	atl1e_configure_dma(adapter);

	/* 12. smb timer to trig interrupt */
	AT_WRITE_REG(hw, REG_SMB_STAT_TIMER, hw->smb_timer);

	intr_status_data = AT_READ_REG(hw, REG_ISR);
	if (unlikely((intr_status_data & ISR_PHY_LINKDOWN) != 0)) {
		netdev_err(adapter->netdev,
			   "atl1e_configure failed, PCIE phy link down\n");
		return -1;
	}

	AT_WRITE_REG(hw, REG_ISR, 0x7fffffff);
	return 0;
}