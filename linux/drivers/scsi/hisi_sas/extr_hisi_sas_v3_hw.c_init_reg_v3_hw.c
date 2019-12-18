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
struct asd_sas_phy {TYPE_1__* phy; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {unsigned long long queue_count; int n_phy; int /*<<< orphan*/  initial_fis_dma; int /*<<< orphan*/  sata_breakpoint_dma; int /*<<< orphan*/  breakpoint_dma; int /*<<< orphan*/  iost_dma; int /*<<< orphan*/  itct_dma; int /*<<< orphan*/ * complete_hdr_dma; int /*<<< orphan*/ * cmd_hdr_dma; struct hisi_sas_phy* phy; } ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;
struct TYPE_2__ {scalar_t__ maximum_linkrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIP_LIMIT ; 
 scalar_t__ ARQOS_ARCACHE_CFG ; 
 scalar_t__ AWQOS_AWCACHE_CFG ; 
 scalar_t__ CFG_AGING_TIME ; 
 scalar_t__ CFG_MAX_TAG ; 
 scalar_t__ CFG_SAS_RAS_INTR_MASK ; 
 int /*<<< orphan*/  CHL_INT0 ; 
 int /*<<< orphan*/  CHL_INT1 ; 
 int /*<<< orphan*/  CHL_INT1_MSK ; 
 int /*<<< orphan*/  CHL_INT2 ; 
 int /*<<< orphan*/  CHL_INT2_MSK ; 
 scalar_t__ CHNL_ENT_INT_MSK ; 
 scalar_t__ CHNL_PHYUPDOWN_INT_MSK ; 
 int /*<<< orphan*/  COARSETUNE_TIME ; 
 scalar_t__ COMPL_Q_0_BASE_ADDR_HI ; 
 scalar_t__ COMPL_Q_0_BASE_ADDR_LO ; 
 scalar_t__ COMPL_Q_0_DEPTH ; 
 int /*<<< orphan*/  CON_CFG_DRIVER ; 
 scalar_t__ CQ_INT_CONVERGE_EN ; 
 scalar_t__ DLVRY_QUEUE_ENABLE ; 
 scalar_t__ DLVRY_Q_0_BASE_ADDR_HI ; 
 scalar_t__ DLVRY_Q_0_BASE_ADDR_LO ; 
 scalar_t__ DLVRY_Q_0_DEPTH ; 
 scalar_t__ ENT_INT_SRC1 ; 
 scalar_t__ ENT_INT_SRC2 ; 
 scalar_t__ ENT_INT_SRC3 ; 
 scalar_t__ ENT_INT_SRC_MSK1 ; 
 scalar_t__ ENT_INT_SRC_MSK2 ; 
 scalar_t__ ENT_INT_SRC_MSK3 ; 
 scalar_t__ HGC_COM_INT_MSK ; 
 scalar_t__ HGC_SAS_TXFAIL_RETRY_CTRL ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 scalar_t__ HYPER_STREAM_ID_EN_CFG ; 
 scalar_t__ INT_COAL_EN ; 
 scalar_t__ IOST_BASE_ADDR_HI ; 
 scalar_t__ IOST_BASE_ADDR_LO ; 
 scalar_t__ IO_BROKEN_MSG_ADDR_HI ; 
 scalar_t__ IO_BROKEN_MSG_ADDR_LO ; 
 scalar_t__ IO_SATA_BROKEN_MSG_ADDR_HI ; 
 scalar_t__ IO_SATA_BROKEN_MSG_ADDR_LO ; 
 scalar_t__ ITCT_BASE_ADDR_HI ; 
 scalar_t__ ITCT_BASE_ADDR_LO ; 
 scalar_t__ OQ0_INT_SRC_MSK ; 
 scalar_t__ OQ_INT_COAL_CNT ; 
 scalar_t__ OQ_INT_COAL_TIME ; 
 scalar_t__ OQ_INT_SRC ; 
 int /*<<< orphan*/  PHYCTRL_DWS_RESET_MSK ; 
 int /*<<< orphan*/  PHYCTRL_NOT_RDY_MSK ; 
 int /*<<< orphan*/  PHYCTRL_OOB_RESTART_MSK ; 
 int /*<<< orphan*/  PHYCTRL_PHY_ENA_MSK ; 
 int /*<<< orphan*/  PHY_CTRL_RDY_MSK ; 
 int /*<<< orphan*/  PROG_PHY_LINK_RATE ; 
 int /*<<< orphan*/  RXOP_CHECK_CFG_H ; 
 scalar_t__ SAS_AXI_USER3 ; 
 scalar_t__ SAS_CFG_DRIVE_VLD ; 
 scalar_t__ SAS_ECC_INTR_MSK ; 
 int /*<<< orphan*/  SAS_EC_INT_COAL_TIME ; 
 scalar_t__ SAS_GPIO_CFG_0 ; 
 scalar_t__ SAS_GPIO_CFG_1 ; 
 scalar_t__ SAS_GPIO_TX_0_1 ; 
 scalar_t__ SAS_LINK_RATE_1_5_GBPS ; 
 scalar_t__ SAS_RAS_INTR0_MASK ; 
 scalar_t__ SAS_RAS_INTR1_MASK ; 
 scalar_t__ SAS_RAS_INTR2_MASK ; 
 int /*<<< orphan*/  SAS_RX_TRAIN_TIMER ; 
 int /*<<< orphan*/  SAS_SSP_CON_TIMER_CFG ; 
 scalar_t__ SATA_INITI_D2H_STORE_ADDR_HI ; 
 scalar_t__ SATA_INITI_D2H_STORE_ADDR_LO ; 
 int /*<<< orphan*/  SERDES_CFG ; 
 int /*<<< orphan*/  SL_RX_BCAST_CHK_MSK ; 
 int /*<<< orphan*/  STP_LINK_TIMER ; 
 int hisi_sas_get_prog_phy_linkrate_mask (int) ; 
 int hisi_sas_intr_conv ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_reg_v3_hw(struct hisi_hba *hisi_hba)
{
	int i;

	/* Global registers init */
	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE,
			 (u32)((1ULL << hisi_hba->queue_count) - 1));
	hisi_sas_write32(hisi_hba, SAS_AXI_USER3, 0);
	hisi_sas_write32(hisi_hba, CFG_MAX_TAG, 0xfff0400);
	hisi_sas_write32(hisi_hba, HGC_SAS_TXFAIL_RETRY_CTRL, 0x108);
	hisi_sas_write32(hisi_hba, CFG_AGING_TIME, 0x1);
	hisi_sas_write32(hisi_hba, INT_COAL_EN, 0x1);
	hisi_sas_write32(hisi_hba, OQ_INT_COAL_TIME, 0x1);
	hisi_sas_write32(hisi_hba, OQ_INT_COAL_CNT, 0x1);
	hisi_sas_write32(hisi_hba, CQ_INT_CONVERGE_EN,
			 hisi_sas_intr_conv);
	hisi_sas_write32(hisi_hba, OQ_INT_SRC, 0xffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC1, 0xffffffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC2, 0xffffffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC3, 0xffffffff);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK1, 0xfefefefe);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK2, 0xfefefefe);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, 0xffc220ff);
	hisi_sas_write32(hisi_hba, CHNL_PHYUPDOWN_INT_MSK, 0x0);
	hisi_sas_write32(hisi_hba, CHNL_ENT_INT_MSK, 0x0);
	hisi_sas_write32(hisi_hba, HGC_COM_INT_MSK, 0x0);
	hisi_sas_write32(hisi_hba, SAS_ECC_INTR_MSK, 0x155555);
	hisi_sas_write32(hisi_hba, AWQOS_AWCACHE_CFG, 0xf0f0);
	hisi_sas_write32(hisi_hba, ARQOS_ARCACHE_CFG, 0xf0f0);
	for (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_write32(hisi_hba, OQ0_INT_SRC_MSK+0x4*i, 0);

	hisi_sas_write32(hisi_hba, HYPER_STREAM_ID_EN_CFG, 1);

	for (i = 0; i < hisi_hba->n_phy; i++) {
		struct hisi_sas_phy *phy = &hisi_hba->phy[i];
		struct asd_sas_phy *sas_phy = &phy->sas_phy;
		u32 prog_phy_link_rate = 0x800;

		if (!sas_phy->phy || (sas_phy->phy->maximum_linkrate <
				SAS_LINK_RATE_1_5_GBPS)) {
			prog_phy_link_rate = 0x855;
		} else {
			enum sas_linkrate max = sas_phy->phy->maximum_linkrate;

			prog_phy_link_rate =
				hisi_sas_get_prog_phy_linkrate_mask(max) |
				0x800;
		}
		hisi_sas_phy_write32(hisi_hba, i, PROG_PHY_LINK_RATE,
			prog_phy_link_rate);
		hisi_sas_phy_write32(hisi_hba, i, SERDES_CFG, 0xffc00);
		hisi_sas_phy_write32(hisi_hba, i, SAS_RX_TRAIN_TIMER, 0x13e80);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT0, 0xffffffff);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT1, 0xffffffff);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT2, 0xffffffff);
		hisi_sas_phy_write32(hisi_hba, i, RXOP_CHECK_CFG_H, 0x1000);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT1_MSK, 0xf2057fff);
		hisi_sas_phy_write32(hisi_hba, i, CHL_INT2_MSK, 0xffffbfe);
		hisi_sas_phy_write32(hisi_hba, i, PHY_CTRL_RDY_MSK, 0x0);
		hisi_sas_phy_write32(hisi_hba, i, PHYCTRL_NOT_RDY_MSK, 0x0);
		hisi_sas_phy_write32(hisi_hba, i, PHYCTRL_DWS_RESET_MSK, 0x0);
		hisi_sas_phy_write32(hisi_hba, i, PHYCTRL_PHY_ENA_MSK, 0x0);
		hisi_sas_phy_write32(hisi_hba, i, SL_RX_BCAST_CHK_MSK, 0x0);
		hisi_sas_phy_write32(hisi_hba, i, PHYCTRL_OOB_RESTART_MSK, 0x1);
		hisi_sas_phy_write32(hisi_hba, i, STP_LINK_TIMER, 0x7f7a120);
		hisi_sas_phy_write32(hisi_hba, i, CON_CFG_DRIVER, 0x2a0a01);
		hisi_sas_phy_write32(hisi_hba, i, SAS_SSP_CON_TIMER_CFG, 0x32);
		hisi_sas_phy_write32(hisi_hba, i, SAS_EC_INT_COAL_TIME,
				     0x30f4240);
		/* used for 12G negotiate */
		hisi_sas_phy_write32(hisi_hba, i, COARSETUNE_TIME, 0x1e);
		hisi_sas_phy_write32(hisi_hba, i, AIP_LIMIT, 0x2ffff);
	}

	for (i = 0; i < hisi_hba->queue_count; i++) {
		/* Delivery queue */
		hisi_sas_write32(hisi_hba,
				 DLVRY_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_write32(hisi_hba, DLVRY_Q_0_BASE_ADDR_LO + (i * 0x14),
				 lower_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_write32(hisi_hba, DLVRY_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SLOTS);

		/* Completion queue */
		hisi_sas_write32(hisi_hba, COMPL_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->complete_hdr_dma[i]));

		hisi_sas_write32(hisi_hba, COMPL_Q_0_BASE_ADDR_LO + (i * 0x14),
				 lower_32_bits(hisi_hba->complete_hdr_dma[i]));

		hisi_sas_write32(hisi_hba, COMPL_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SLOTS);
	}

	/* itct */
	hisi_sas_write32(hisi_hba, ITCT_BASE_ADDR_LO,
			 lower_32_bits(hisi_hba->itct_dma));

	hisi_sas_write32(hisi_hba, ITCT_BASE_ADDR_HI,
			 upper_32_bits(hisi_hba->itct_dma));

	/* iost */
	hisi_sas_write32(hisi_hba, IOST_BASE_ADDR_LO,
			 lower_32_bits(hisi_hba->iost_dma));

	hisi_sas_write32(hisi_hba, IOST_BASE_ADDR_HI,
			 upper_32_bits(hisi_hba->iost_dma));

	/* breakpoint */
	hisi_sas_write32(hisi_hba, IO_BROKEN_MSG_ADDR_LO,
			 lower_32_bits(hisi_hba->breakpoint_dma));

	hisi_sas_write32(hisi_hba, IO_BROKEN_MSG_ADDR_HI,
			 upper_32_bits(hisi_hba->breakpoint_dma));

	/* SATA broken msg */
	hisi_sas_write32(hisi_hba, IO_SATA_BROKEN_MSG_ADDR_LO,
			 lower_32_bits(hisi_hba->sata_breakpoint_dma));

	hisi_sas_write32(hisi_hba, IO_SATA_BROKEN_MSG_ADDR_HI,
			 upper_32_bits(hisi_hba->sata_breakpoint_dma));

	/* SATA initial fis */
	hisi_sas_write32(hisi_hba, SATA_INITI_D2H_STORE_ADDR_LO,
			 lower_32_bits(hisi_hba->initial_fis_dma));

	hisi_sas_write32(hisi_hba, SATA_INITI_D2H_STORE_ADDR_HI,
			 upper_32_bits(hisi_hba->initial_fis_dma));

	/* RAS registers init */
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR0_MASK, 0x0);
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR1_MASK, 0x0);
	hisi_sas_write32(hisi_hba, SAS_RAS_INTR2_MASK, 0x0);
	hisi_sas_write32(hisi_hba, CFG_SAS_RAS_INTR_MASK, 0x0);

	/* LED registers init */
	hisi_sas_write32(hisi_hba, SAS_CFG_DRIVE_VLD, 0x80000ff);
	hisi_sas_write32(hisi_hba, SAS_GPIO_TX_0_1, 0x80808080);
	hisi_sas_write32(hisi_hba, SAS_GPIO_TX_0_1 + 0x4, 0x80808080);
	/* Configure blink generator rate A to 1Hz and B to 4Hz */
	hisi_sas_write32(hisi_hba, SAS_GPIO_CFG_1, 0x121700);
	hisi_sas_write32(hisi_hba, SAS_GPIO_CFG_0, 0x800000);
}