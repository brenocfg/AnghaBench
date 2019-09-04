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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct alx_hw {unsigned long smb_timer; int imt; int ith_tpd; int dma_chnl; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rx_ctrl; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_CLK_GATE ; 
 int ALX_CLK_GATE_ALL ; 
 int ALX_DEV_CTRL_MAXRRS_MIN ; 
 int /*<<< orphan*/  ALX_DMA ; 
 int ALX_DMA_RCHNL_SEL_SHIFT ; 
 int ALX_DMA_RDLY_CNT_DEF ; 
 int ALX_DMA_RDLY_CNT_SHIFT ; 
 int ALX_DMA_RORDER_MODE_OUT ; 
 int ALX_DMA_RORDER_MODE_SHIFT ; 
 int ALX_DMA_RREQ_BLEN_SHIFT ; 
 int ALX_DMA_RREQ_PRI_DATA ; 
 int ALX_DMA_WDLY_CNT_DEF ; 
 int ALX_DMA_WDLY_CNT_SHIFT ; 
 int ALX_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALX_HQTPD ; 
 int ALX_HQTPD_BURST_EN ; 
 int ALX_HQTPD_Q1_NUMPREF_SHIFT ; 
 int ALX_HQTPD_Q2_NUMPREF_SHIFT ; 
 int ALX_HQTPD_Q3_NUMPREF_SHIFT ; 
 int /*<<< orphan*/  ALX_IDLE_DECISN_TIMER ; 
 int ALX_IDLE_DECISN_TIMER_DEF ; 
 int /*<<< orphan*/  ALX_INT_RETRIG ; 
 int ALX_INT_RETRIG_TO ; 
 int /*<<< orphan*/  ALX_IRQ_MODU_TIMER ; 
 int ALX_IRQ_MODU_TIMER1_SHIFT ; 
 int /*<<< orphan*/  ALX_MAC_CTRL_FAST_PAUSE ; 
 int /*<<< orphan*/  ALX_MASTER ; 
 int ALX_MASTER_IRQMOD1_EN ; 
 int ALX_MASTER_IRQMOD2_EN ; 
 int ALX_MASTER_SYSALVTIMER_EN ; 
 int /*<<< orphan*/  ALX_MTU ; 
 int ALX_MTU_JUMBO_TH ; 
 int ALX_MTU_STD_ALGN ; 
 int ALX_RAW_MTU (int /*<<< orphan*/ ) ; 
 scalar_t__ ALX_REV_B0 ; 
 int /*<<< orphan*/  ALX_RXQ0 ; 
 int /*<<< orphan*/  ALX_RXQ0_ASPM_THRESH ; 
 int /*<<< orphan*/  ALX_RXQ0_ASPM_THRESH_100M ; 
 int ALX_RXQ0_IDT_TBL_SIZE_DEF ; 
 int ALX_RXQ0_IDT_TBL_SIZE_SHIFT ; 
 int ALX_RXQ0_IPV6_PARSE_EN ; 
 int ALX_RXQ0_NUM_RFD_PREF_DEF ; 
 int ALX_RXQ0_NUM_RFD_PREF_SHIFT ; 
 int ALX_RXQ0_RSS_HASH_EN ; 
 int ALX_RXQ0_RSS_HSTYP_ALL ; 
 int ALX_RXQ0_RSS_MODE_DIS ; 
 int ALX_RXQ0_RSS_MODE_SHIFT ; 
 int /*<<< orphan*/  ALX_RXQ2 ; 
 int ALX_RXQ2_RXF_FLOW_CTRL_RSVD ; 
 int ALX_RXQ2_RXF_XOFF_THRESH_SHIFT ; 
 int ALX_RXQ2_RXF_XON_THRESH_SHIFT ; 
 int /*<<< orphan*/  ALX_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALX_SMB_TIMER ; 
 int /*<<< orphan*/  ALX_SRAM5 ; 
 int /*<<< orphan*/  ALX_SRAM_RXF_LEN ; 
 int ALX_SRAM_RXF_LEN_8K ; 
 int /*<<< orphan*/  ALX_TINT_TIMER ; 
 int /*<<< orphan*/  ALX_TINT_TPD_THRSHLD ; 
 int /*<<< orphan*/  ALX_TXQ0 ; 
 int ALX_TXQ0_LSO_8023_EN ; 
 int ALX_TXQ0_MODE_ENHANCE ; 
 int ALX_TXQ0_SUPT_IPOPT ; 
 int ALX_TXQ0_TPD_BURSTPREF_SHIFT ; 
 int ALX_TXQ0_TXF_BURST_PREF_SHIFT ; 
 int /*<<< orphan*/  ALX_TXQ1 ; 
 int ALX_TXQ1_ERRLGPKT_DROP_EN ; 
 int ALX_TXQ1_JUMBO_TSO_TH ; 
 int ALX_TXQ_TPD_BURSTPREF_DEF ; 
 int ALX_TXQ_TXF_BURST_PREF_DEF ; 
 int /*<<< orphan*/  ALX_WRR ; 
 int ALX_WRR_PRI0_SHIFT ; 
 int ALX_WRR_PRI1_SHIFT ; 
 int ALX_WRR_PRI2_SHIFT ; 
 int ALX_WRR_PRI3_SHIFT ; 
 int ALX_WRR_PRI_RESTRICT_NONE ; 
 int ALX_WRR_PRI_SHIFT ; 
 int ETH_FCS_LEN ; 
 int VLAN_HLEN ; 
 scalar_t__ alx_hw_giga (struct alx_hw*) ; 
 scalar_t__ alx_hw_revision (struct alx_hw*) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_set_macaddr (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int pcie_get_readrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_set_readrq (int /*<<< orphan*/ ,int) ; 

void alx_configure_basic(struct alx_hw *hw)
{
	u32 val, raw_mtu, max_payload;
	u16 val16;
	u8 chip_rev = alx_hw_revision(hw);

	alx_set_macaddr(hw, hw->mac_addr);

	alx_write_mem32(hw, ALX_CLK_GATE, ALX_CLK_GATE_ALL);

	/* idle timeout to switch clk_125M */
	if (chip_rev >= ALX_REV_B0)
		alx_write_mem32(hw, ALX_IDLE_DECISN_TIMER,
				ALX_IDLE_DECISN_TIMER_DEF);

	alx_write_mem32(hw, ALX_SMB_TIMER, hw->smb_timer * 500UL);

	val = alx_read_mem32(hw, ALX_MASTER);
	val |= ALX_MASTER_IRQMOD2_EN |
	       ALX_MASTER_IRQMOD1_EN |
	       ALX_MASTER_SYSALVTIMER_EN;
	alx_write_mem32(hw, ALX_MASTER, val);
	alx_write_mem32(hw, ALX_IRQ_MODU_TIMER,
			(hw->imt >> 1) << ALX_IRQ_MODU_TIMER1_SHIFT);
	/* intr re-trig timeout */
	alx_write_mem32(hw, ALX_INT_RETRIG, ALX_INT_RETRIG_TO);
	/* tpd threshold to trig int */
	alx_write_mem32(hw, ALX_TINT_TPD_THRSHLD, hw->ith_tpd);
	alx_write_mem32(hw, ALX_TINT_TIMER, hw->imt);

	raw_mtu = ALX_RAW_MTU(hw->mtu);
	alx_write_mem32(hw, ALX_MTU, raw_mtu);
	if (raw_mtu > (ALX_MTU_JUMBO_TH + ETH_FCS_LEN + VLAN_HLEN))
		hw->rx_ctrl &= ~ALX_MAC_CTRL_FAST_PAUSE;

	if (raw_mtu < ALX_TXQ1_JUMBO_TSO_TH)
		val = (raw_mtu + 7) >> 3;
	else
		val = ALX_TXQ1_JUMBO_TSO_TH >> 3;
	alx_write_mem32(hw, ALX_TXQ1, val | ALX_TXQ1_ERRLGPKT_DROP_EN);

	max_payload = pcie_get_readrq(hw->pdev) >> 8;
	/*
	 * if BIOS had changed the default dma read max length,
	 * restore it to default value
	 */
	if (max_payload < ALX_DEV_CTRL_MAXRRS_MIN)
		pcie_set_readrq(hw->pdev, 128 << ALX_DEV_CTRL_MAXRRS_MIN);

	val = ALX_TXQ_TPD_BURSTPREF_DEF << ALX_TXQ0_TPD_BURSTPREF_SHIFT |
	      ALX_TXQ0_MODE_ENHANCE | ALX_TXQ0_LSO_8023_EN |
	      ALX_TXQ0_SUPT_IPOPT |
	      ALX_TXQ_TXF_BURST_PREF_DEF << ALX_TXQ0_TXF_BURST_PREF_SHIFT;
	alx_write_mem32(hw, ALX_TXQ0, val);
	val = ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q1_NUMPREF_SHIFT |
	      ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q2_NUMPREF_SHIFT |
	      ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q3_NUMPREF_SHIFT |
	      ALX_HQTPD_BURST_EN;
	alx_write_mem32(hw, ALX_HQTPD, val);

	/* rxq, flow control */
	val = alx_read_mem32(hw, ALX_SRAM5);
	val = ALX_GET_FIELD(val, ALX_SRAM_RXF_LEN) << 3;
	if (val > ALX_SRAM_RXF_LEN_8K) {
		val16 = ALX_MTU_STD_ALGN >> 3;
		val = (val - ALX_RXQ2_RXF_FLOW_CTRL_RSVD) >> 3;
	} else {
		val16 = ALX_MTU_STD_ALGN >> 3;
		val = (val - ALX_MTU_STD_ALGN) >> 3;
	}
	alx_write_mem32(hw, ALX_RXQ2,
			val16 << ALX_RXQ2_RXF_XOFF_THRESH_SHIFT |
			val << ALX_RXQ2_RXF_XON_THRESH_SHIFT);
	val = ALX_RXQ0_NUM_RFD_PREF_DEF << ALX_RXQ0_NUM_RFD_PREF_SHIFT |
	      ALX_RXQ0_RSS_MODE_DIS << ALX_RXQ0_RSS_MODE_SHIFT |
	      ALX_RXQ0_IDT_TBL_SIZE_DEF << ALX_RXQ0_IDT_TBL_SIZE_SHIFT |
	      ALX_RXQ0_RSS_HSTYP_ALL | ALX_RXQ0_RSS_HASH_EN |
	      ALX_RXQ0_IPV6_PARSE_EN;

	if (alx_hw_giga(hw))
		ALX_SET_FIELD(val, ALX_RXQ0_ASPM_THRESH,
			      ALX_RXQ0_ASPM_THRESH_100M);

	alx_write_mem32(hw, ALX_RXQ0, val);

	val = alx_read_mem32(hw, ALX_DMA);
	val = ALX_DMA_RORDER_MODE_OUT << ALX_DMA_RORDER_MODE_SHIFT |
	      ALX_DMA_RREQ_PRI_DATA |
	      max_payload << ALX_DMA_RREQ_BLEN_SHIFT |
	      ALX_DMA_WDLY_CNT_DEF << ALX_DMA_WDLY_CNT_SHIFT |
	      ALX_DMA_RDLY_CNT_DEF << ALX_DMA_RDLY_CNT_SHIFT |
	      (hw->dma_chnl - 1) << ALX_DMA_RCHNL_SEL_SHIFT;
	alx_write_mem32(hw, ALX_DMA, val);

	/* default multi-tx-q weights */
	val = ALX_WRR_PRI_RESTRICT_NONE << ALX_WRR_PRI_SHIFT |
	      4 << ALX_WRR_PRI0_SHIFT |
	      4 << ALX_WRR_PRI1_SHIFT |
	      4 << ALX_WRR_PRI2_SHIFT |
	      4 << ALX_WRR_PRI3_SHIFT;
	alx_write_mem32(hw, ALX_WRR, val);
}