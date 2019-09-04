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
struct atl1c_hw {int ctrl_flags; scalar_t__ nic_type; int ict; int tx_imt; int rx_imt; int smb_timer; int max_frame_size; } ;
struct atl1c_adapter {struct atl1c_hw hw; } ;

/* Variables and functions */
 int ATL1C_CLK_GATING_EN ; 
 int ATL1C_INTR_CLEAR_ON_READ ; 
 int ATL1C_INTR_MODRT_ENABLE ; 
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int CLK_GATING_EN_ALL ; 
 int CLK_GATING_RXMAC_EN ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int INT_RETRIG_TIMER_MASK ; 
 int IRQ_MODRT_RX_TIMER_SHIFT ; 
 int IRQ_MODRT_TIMER_MASK ; 
 int IRQ_MODRT_TX_TIMER_SHIFT ; 
 int MASTER_CTRL_INT_RDCLR ; 
 int MASTER_CTRL_RX_ITIMER_EN ; 
 int MASTER_CTRL_SA_TIMER_EN ; 
 int MASTER_CTRL_TX_ITIMER_EN ; 
 int /*<<< orphan*/  REG_CLK_GATING_CTRL ; 
 int /*<<< orphan*/  REG_INT_RETRIG_TIMER ; 
 int /*<<< orphan*/  REG_IRQ_MODRT_TIMER_INIT ; 
 int /*<<< orphan*/  REG_ISR ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  REG_MTU ; 
 int /*<<< orphan*/  REG_SMB_STAT_TIMER ; 
 int /*<<< orphan*/  REG_WOL_CTRL ; 
 int SMB_STAT_TIMER_MASK ; 
 int VLAN_HLEN ; 
 scalar_t__ athr_l2c_b ; 
 int /*<<< orphan*/  atl1c_configure_des_ring (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_configure_dma (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_configure_rx (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_configure_tx (struct atl1c_adapter*) ; 

__attribute__((used)) static int atl1c_configure_mac(struct atl1c_adapter *adapter)
{
	struct atl1c_hw *hw = &adapter->hw;
	u32 master_ctrl_data = 0;
	u32 intr_modrt_data;
	u32 data;

	AT_READ_REG(hw, REG_MASTER_CTRL, &master_ctrl_data);
	master_ctrl_data &= ~(MASTER_CTRL_TX_ITIMER_EN |
			      MASTER_CTRL_RX_ITIMER_EN |
			      MASTER_CTRL_INT_RDCLR);
	/* clear interrupt status */
	AT_WRITE_REG(hw, REG_ISR, 0xFFFFFFFF);
	/*  Clear any WOL status */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);
	/* set Interrupt Clear Timer
	 * HW will enable self to assert interrupt event to system after
	 * waiting x-time for software to notify it accept interrupt.
	 */

	data = CLK_GATING_EN_ALL;
	if (hw->ctrl_flags & ATL1C_CLK_GATING_EN) {
		if (hw->nic_type == athr_l2c_b)
			data &= ~CLK_GATING_RXMAC_EN;
	} else
		data = 0;
	AT_WRITE_REG(hw, REG_CLK_GATING_CTRL, data);

	AT_WRITE_REG(hw, REG_INT_RETRIG_TIMER,
		hw->ict & INT_RETRIG_TIMER_MASK);

	atl1c_configure_des_ring(adapter);

	if (hw->ctrl_flags & ATL1C_INTR_MODRT_ENABLE) {
		intr_modrt_data = (hw->tx_imt & IRQ_MODRT_TIMER_MASK) <<
					IRQ_MODRT_TX_TIMER_SHIFT;
		intr_modrt_data |= (hw->rx_imt & IRQ_MODRT_TIMER_MASK) <<
					IRQ_MODRT_RX_TIMER_SHIFT;
		AT_WRITE_REG(hw, REG_IRQ_MODRT_TIMER_INIT, intr_modrt_data);
		master_ctrl_data |=
			MASTER_CTRL_TX_ITIMER_EN | MASTER_CTRL_RX_ITIMER_EN;
	}

	if (hw->ctrl_flags & ATL1C_INTR_CLEAR_ON_READ)
		master_ctrl_data |= MASTER_CTRL_INT_RDCLR;

	master_ctrl_data |= MASTER_CTRL_SA_TIMER_EN;
	AT_WRITE_REG(hw, REG_MASTER_CTRL, master_ctrl_data);

	AT_WRITE_REG(hw, REG_SMB_STAT_TIMER,
		hw->smb_timer & SMB_STAT_TIMER_MASK);

	/* set MTU */
	AT_WRITE_REG(hw, REG_MTU, hw->max_frame_size + ETH_HLEN +
			VLAN_HLEN + ETH_FCS_LEN);

	atl1c_configure_tx(adapter);
	atl1c_configure_rx(adapter);
	atl1c_configure_dma(adapter);

	return 0;
}