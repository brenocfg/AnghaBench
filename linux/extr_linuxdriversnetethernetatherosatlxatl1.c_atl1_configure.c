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
struct atl1_hw {int max_frame_size; int dev_rev; scalar_t__ rcb_value; int cmb_tpd; int cmb_rrd; int cmb_rx_timer; int smb_timer; scalar_t__ hw_addr; scalar_t__ cmb_tx_timer; scalar_t__ dma_ord; scalar_t__ dmaw_block; scalar_t__ dmar_block; scalar_t__ rfd_fetch_gap; scalar_t__ rrd_burst; scalar_t__ rfd_burst; scalar_t__ tpd_fetch_gap; scalar_t__ tx_jumbo_task_th; scalar_t__ tpd_fetch_th; scalar_t__ txf_burst; scalar_t__ tpd_burst; scalar_t__ rrd_ret_timer; scalar_t__ rx_jumbo_lkah; scalar_t__ rx_jumbo_th; scalar_t__ jam_ipg; scalar_t__ max_retry; scalar_t__ lcol; scalar_t__ ipgr2; scalar_t__ ipgr1; scalar_t__ min_ifg; scalar_t__ ipgt; scalar_t__* mac_addr; } ;
struct TYPE_9__ {int dma; int count; int /*<<< orphan*/  next_to_use; } ;
struct TYPE_7__ {int dma; int /*<<< orphan*/  next_to_use; scalar_t__ count; } ;
struct TYPE_8__ {int dma; int count; int /*<<< orphan*/  next_to_clean; } ;
struct TYPE_6__ {int dma; } ;
struct TYPE_10__ {int dma; } ;
struct atl1_adapter {struct atl1_hw hw; TYPE_4__ tpd_ring; int /*<<< orphan*/  ict; int /*<<< orphan*/  imt; TYPE_2__ rfd_ring; TYPE_3__ rrd_ring; TYPE_1__ smb; TYPE_5__ cmb; } ;

/* Variables and functions */
 int CSMB_CTRL_CMB_EN ; 
 int CSMB_CTRL_SMB_EN ; 
 int DMA_CTRL_DMAR_BURST_LEN_MASK ; 
 int DMA_CTRL_DMAR_BURST_LEN_SHIFT ; 
 int DMA_CTRL_DMAR_EN ; 
 int DMA_CTRL_DMAW_BURST_LEN_MASK ; 
 int DMA_CTRL_DMAW_BURST_LEN_SHIFT ; 
 int DMA_CTRL_DMAW_EN ; 
 int DMA_CTRL_RCB_VALUE ; 
 int ISR_PHY_LINKDOWN ; 
 int MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT ; 
 int MAC_HALF_DUPLX_CTRL_EXC_DEF_EN ; 
 int MAC_HALF_DUPLX_CTRL_JAMIPG_MASK ; 
 int MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT ; 
 int MAC_HALF_DUPLX_CTRL_LCOL_MASK ; 
 int MAC_HALF_DUPLX_CTRL_RETRY_MASK ; 
 int MAC_HALF_DUPLX_CTRL_RETRY_SHIFT ; 
 int MAC_IPG_IFG_IPGR1_MASK ; 
 int MAC_IPG_IFG_IPGR1_SHIFT ; 
 int MAC_IPG_IFG_IPGR2_MASK ; 
 int MAC_IPG_IFG_IPGR2_SHIFT ; 
 int MAC_IPG_IFG_IPGT_MASK ; 
 int MAC_IPG_IFG_IPGT_SHIFT ; 
 int MAC_IPG_IFG_MIFG_MASK ; 
 int MAC_IPG_IFG_MIFG_SHIFT ; 
 int MASTER_CTRL_ITIMER_EN ; 
 int MB_RFD_PROD_INDX_MASK ; 
 int MB_RFD_PROD_INDX_SHIFT ; 
 int MB_RRD_CONS_INDX_MASK ; 
 int MB_RRD_CONS_INDX_SHIFT ; 
 int MB_TPD_PROD_INDX_MASK ; 
 int MB_TPD_PROD_INDX_SHIFT ; 
 scalar_t__ REG_CMBDISDMA_TIMER ; 
 scalar_t__ REG_CMB_WRITE_TH ; 
 scalar_t__ REG_CMB_WRITE_TIMER ; 
 scalar_t__ REG_CSMB_CTRL ; 
 scalar_t__ REG_DESC_BASE_ADDR_HI ; 
 scalar_t__ REG_DESC_CMB_ADDR_LO ; 
 scalar_t__ REG_DESC_RFD_ADDR_LO ; 
 scalar_t__ REG_DESC_RFD_RRD_RING_SIZE ; 
 scalar_t__ REG_DESC_RRD_ADDR_LO ; 
 scalar_t__ REG_DESC_SMB_ADDR_LO ; 
 scalar_t__ REG_DESC_TPD_ADDR_LO ; 
 scalar_t__ REG_DESC_TPD_RING_SIZE ; 
 scalar_t__ REG_DMA_CTRL ; 
 scalar_t__ REG_IRQ_MODU_TIMER_INIT ; 
 scalar_t__ REG_ISR ; 
 scalar_t__ REG_LOAD_PTR ; 
 scalar_t__ REG_MAC_HALF_DUPLX_CTRL ; 
 scalar_t__ REG_MAC_IPG_IFG ; 
 scalar_t__ REG_MAC_STA_ADDR ; 
 scalar_t__ REG_MAILBOX ; 
 scalar_t__ REG_MASTER_CTRL ; 
 scalar_t__ REG_MTU ; 
 scalar_t__ REG_RXQ_CTRL ; 
 scalar_t__ REG_RXQ_JMBOSZ_RRDTIM ; 
 scalar_t__ REG_SMB_TIMER ; 
 scalar_t__ REG_TXQ_CTRL ; 
 scalar_t__ REG_TX_JUMBO_TASK_TH_TPD_IPG ; 
 int RXQ_CTRL_CUT_THRU_EN ; 
 int RXQ_CTRL_EN ; 
 int RXQ_CTRL_RFD_BURST_NUM_MASK ; 
 int RXQ_CTRL_RFD_BURST_NUM_SHIFT ; 
 int RXQ_CTRL_RFD_PREF_MIN_IPG_MASK ; 
 int RXQ_CTRL_RFD_PREF_MIN_IPG_SHIFT ; 
 int RXQ_CTRL_RRD_BURST_THRESH_MASK ; 
 int RXQ_CTRL_RRD_BURST_THRESH_SHIFT ; 
 int RXQ_JMBOSZ_TH_MASK ; 
 int RXQ_JMBOSZ_TH_SHIFT ; 
 int RXQ_JMBO_LKAH_MASK ; 
 int RXQ_JMBO_LKAH_SHIFT ; 
 int RXQ_RRD_TIMER_MASK ; 
 int RXQ_RRD_TIMER_SHIFT ; 
 int TXQ_CTRL_EN ; 
 int TXQ_CTRL_ENH_MODE ; 
 int TXQ_CTRL_TPD_BURST_NUM_MASK ; 
 int TXQ_CTRL_TPD_BURST_NUM_SHIFT ; 
 int TXQ_CTRL_TPD_FETCH_TH_MASK ; 
 int TXQ_CTRL_TPD_FETCH_TH_SHIFT ; 
 int TXQ_CTRL_TXF_BURST_NUM_MASK ; 
 int TXQ_CTRL_TXF_BURST_NUM_SHIFT ; 
 int TX_JUMBO_TASK_TH_MASK ; 
 int TX_JUMBO_TASK_TH_SHIFT ; 
 int TX_TPD_MIN_IPG_MASK ; 
 int TX_TPD_MIN_IPG_SHIFT ; 
 scalar_t__ atl1_rcb_128 ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  set_flow_ctrl_new (struct atl1_hw*) ; 
 int /*<<< orphan*/  set_flow_ctrl_old (struct atl1_adapter*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 atl1_configure(struct atl1_adapter *adapter)
{
	struct atl1_hw *hw = &adapter->hw;
	u32 value;

	/* clear interrupt status */
	iowrite32(0xffffffff, adapter->hw.hw_addr + REG_ISR);

	/* set MAC Address */
	value = (((u32) hw->mac_addr[2]) << 24) |
		(((u32) hw->mac_addr[3]) << 16) |
		(((u32) hw->mac_addr[4]) << 8) |
		(((u32) hw->mac_addr[5]));
	iowrite32(value, hw->hw_addr + REG_MAC_STA_ADDR);
	value = (((u32) hw->mac_addr[0]) << 8) | (((u32) hw->mac_addr[1]));
	iowrite32(value, hw->hw_addr + (REG_MAC_STA_ADDR + 4));

	/* tx / rx ring */

	/* HI base address */
	iowrite32((u32) ((adapter->tpd_ring.dma & 0xffffffff00000000ULL) >> 32),
		hw->hw_addr + REG_DESC_BASE_ADDR_HI);
	/* LO base address */
	iowrite32((u32) (adapter->rfd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_RFD_ADDR_LO);
	iowrite32((u32) (adapter->rrd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_RRD_ADDR_LO);
	iowrite32((u32) (adapter->tpd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_TPD_ADDR_LO);
	iowrite32((u32) (adapter->cmb.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_CMB_ADDR_LO);
	iowrite32((u32) (adapter->smb.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_SMB_ADDR_LO);

	/* element count */
	value = adapter->rrd_ring.count;
	value <<= 16;
	value += adapter->rfd_ring.count;
	iowrite32(value, hw->hw_addr + REG_DESC_RFD_RRD_RING_SIZE);
	iowrite32(adapter->tpd_ring.count, hw->hw_addr +
		REG_DESC_TPD_RING_SIZE);

	/* Load Ptr */
	iowrite32(1, hw->hw_addr + REG_LOAD_PTR);

	/* config Mailbox */
	value = ((atomic_read(&adapter->tpd_ring.next_to_use)
		  & MB_TPD_PROD_INDX_MASK) << MB_TPD_PROD_INDX_SHIFT) |
		((atomic_read(&adapter->rrd_ring.next_to_clean)
		& MB_RRD_CONS_INDX_MASK) << MB_RRD_CONS_INDX_SHIFT) |
		((atomic_read(&adapter->rfd_ring.next_to_use)
		& MB_RFD_PROD_INDX_MASK) << MB_RFD_PROD_INDX_SHIFT);
	iowrite32(value, hw->hw_addr + REG_MAILBOX);

	/* config IPG/IFG */
	value = (((u32) hw->ipgt & MAC_IPG_IFG_IPGT_MASK)
		 << MAC_IPG_IFG_IPGT_SHIFT) |
		(((u32) hw->min_ifg & MAC_IPG_IFG_MIFG_MASK)
		<< MAC_IPG_IFG_MIFG_SHIFT) |
		(((u32) hw->ipgr1 & MAC_IPG_IFG_IPGR1_MASK)
		<< MAC_IPG_IFG_IPGR1_SHIFT) |
		(((u32) hw->ipgr2 & MAC_IPG_IFG_IPGR2_MASK)
		<< MAC_IPG_IFG_IPGR2_SHIFT);
	iowrite32(value, hw->hw_addr + REG_MAC_IPG_IFG);

	/* config  Half-Duplex Control */
	value = ((u32) hw->lcol & MAC_HALF_DUPLX_CTRL_LCOL_MASK) |
		(((u32) hw->max_retry & MAC_HALF_DUPLX_CTRL_RETRY_MASK)
		<< MAC_HALF_DUPLX_CTRL_RETRY_SHIFT) |
		MAC_HALF_DUPLX_CTRL_EXC_DEF_EN |
		(0xa << MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT) |
		(((u32) hw->jam_ipg & MAC_HALF_DUPLX_CTRL_JAMIPG_MASK)
		<< MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT);
	iowrite32(value, hw->hw_addr + REG_MAC_HALF_DUPLX_CTRL);

	/* set Interrupt Moderator Timer */
	iowrite16(adapter->imt, hw->hw_addr + REG_IRQ_MODU_TIMER_INIT);
	iowrite32(MASTER_CTRL_ITIMER_EN, hw->hw_addr + REG_MASTER_CTRL);

	/* set Interrupt Clear Timer */
	iowrite16(adapter->ict, hw->hw_addr + REG_CMBDISDMA_TIMER);

	/* set max frame size hw will accept */
	iowrite32(hw->max_frame_size, hw->hw_addr + REG_MTU);

	/* jumbo size & rrd retirement timer */
	value = (((u32) hw->rx_jumbo_th & RXQ_JMBOSZ_TH_MASK)
		 << RXQ_JMBOSZ_TH_SHIFT) |
		(((u32) hw->rx_jumbo_lkah & RXQ_JMBO_LKAH_MASK)
		<< RXQ_JMBO_LKAH_SHIFT) |
		(((u32) hw->rrd_ret_timer & RXQ_RRD_TIMER_MASK)
		<< RXQ_RRD_TIMER_SHIFT);
	iowrite32(value, hw->hw_addr + REG_RXQ_JMBOSZ_RRDTIM);

	/* Flow Control */
	switch (hw->dev_rev) {
	case 0x8001:
	case 0x9001:
	case 0x9002:
	case 0x9003:
		set_flow_ctrl_old(adapter);
		break;
	default:
		set_flow_ctrl_new(hw);
		break;
	}

	/* config TXQ */
	value = (((u32) hw->tpd_burst & TXQ_CTRL_TPD_BURST_NUM_MASK)
		 << TXQ_CTRL_TPD_BURST_NUM_SHIFT) |
		(((u32) hw->txf_burst & TXQ_CTRL_TXF_BURST_NUM_MASK)
		<< TXQ_CTRL_TXF_BURST_NUM_SHIFT) |
		(((u32) hw->tpd_fetch_th & TXQ_CTRL_TPD_FETCH_TH_MASK)
		<< TXQ_CTRL_TPD_FETCH_TH_SHIFT) | TXQ_CTRL_ENH_MODE |
		TXQ_CTRL_EN;
	iowrite32(value, hw->hw_addr + REG_TXQ_CTRL);

	/* min tpd fetch gap & tx jumbo packet size threshold for taskoffload */
	value = (((u32) hw->tx_jumbo_task_th & TX_JUMBO_TASK_TH_MASK)
		<< TX_JUMBO_TASK_TH_SHIFT) |
		(((u32) hw->tpd_fetch_gap & TX_TPD_MIN_IPG_MASK)
		<< TX_TPD_MIN_IPG_SHIFT);
	iowrite32(value, hw->hw_addr + REG_TX_JUMBO_TASK_TH_TPD_IPG);

	/* config RXQ */
	value = (((u32) hw->rfd_burst & RXQ_CTRL_RFD_BURST_NUM_MASK)
		<< RXQ_CTRL_RFD_BURST_NUM_SHIFT) |
		(((u32) hw->rrd_burst & RXQ_CTRL_RRD_BURST_THRESH_MASK)
		<< RXQ_CTRL_RRD_BURST_THRESH_SHIFT) |
		(((u32) hw->rfd_fetch_gap & RXQ_CTRL_RFD_PREF_MIN_IPG_MASK)
		<< RXQ_CTRL_RFD_PREF_MIN_IPG_SHIFT) | RXQ_CTRL_CUT_THRU_EN |
		RXQ_CTRL_EN;
	iowrite32(value, hw->hw_addr + REG_RXQ_CTRL);

	/* config DMA Engine */
	value = ((((u32) hw->dmar_block) & DMA_CTRL_DMAR_BURST_LEN_MASK)
		<< DMA_CTRL_DMAR_BURST_LEN_SHIFT) |
		((((u32) hw->dmaw_block) & DMA_CTRL_DMAW_BURST_LEN_MASK)
		<< DMA_CTRL_DMAW_BURST_LEN_SHIFT) | DMA_CTRL_DMAR_EN |
		DMA_CTRL_DMAW_EN;
	value |= (u32) hw->dma_ord;
	if (atl1_rcb_128 == hw->rcb_value)
		value |= DMA_CTRL_RCB_VALUE;
	iowrite32(value, hw->hw_addr + REG_DMA_CTRL);

	/* config CMB / SMB */
	value = (hw->cmb_tpd > adapter->tpd_ring.count) ?
		hw->cmb_tpd : adapter->tpd_ring.count;
	value <<= 16;
	value |= hw->cmb_rrd;
	iowrite32(value, hw->hw_addr + REG_CMB_WRITE_TH);
	value = hw->cmb_rx_timer | ((u32) hw->cmb_tx_timer << 16);
	iowrite32(value, hw->hw_addr + REG_CMB_WRITE_TIMER);
	iowrite32(hw->smb_timer, hw->hw_addr + REG_SMB_TIMER);

	/* --- enable CMB / SMB */
	value = CSMB_CTRL_CMB_EN | CSMB_CTRL_SMB_EN;
	iowrite32(value, hw->hw_addr + REG_CSMB_CTRL);

	value = ioread32(adapter->hw.hw_addr + REG_ISR);
	if (unlikely((value & ISR_PHY_LINKDOWN) != 0))
		value = 1;	/* config failed */
	else
		value = 0;

	/* clear all interrupt status */
	iowrite32(0x3fffffff, adapter->hw.hw_addr + REG_ISR);
	iowrite32(0, adapter->hw.hw_addr + REG_ISR);
	return value;
}