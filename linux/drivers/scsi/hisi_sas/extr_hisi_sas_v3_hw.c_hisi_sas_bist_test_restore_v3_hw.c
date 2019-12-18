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
struct hisi_hba {int debugfs_bist_phy_no; } ;

/* Variables and functions */
 int CFG_ALOS_CHK_DISABLE_MSK ; 
 int CFG_BIST_TEST_MSK ; 
 int CFG_PROG_PHY_LINK_RATE_MSK ; 
 int CFG_PROG_PHY_LINK_RATE_OFF ; 
 int CFG_RX_BIST_EN_MSK ; 
 int CFG_TX_BIST_EN_MSK ; 
 int /*<<< orphan*/  PROG_PHY_LINK_RATE ; 
 int /*<<< orphan*/  SAS_PHY_BIST_CTRL ; 
 int /*<<< orphan*/  SERDES_CFG ; 
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hisi_sas_bist_test_restore_v3_hw(struct hisi_hba *hisi_hba)
{
	u32 reg_val;
	int phy_id = hisi_hba->debugfs_bist_phy_no;

	/* disable loopback */
	reg_val = hisi_sas_phy_read32(hisi_hba, phy_id, SAS_PHY_BIST_CTRL);
	reg_val &= ~(CFG_RX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK |
		     CFG_BIST_TEST_MSK);
	hisi_sas_phy_write32(hisi_hba, phy_id, SAS_PHY_BIST_CTRL, reg_val);

	/* enable ALOS */
	reg_val = hisi_sas_phy_read32(hisi_hba, phy_id, SERDES_CFG);
	reg_val &= ~CFG_ALOS_CHK_DISABLE_MSK;
	hisi_sas_phy_write32(hisi_hba, phy_id, SERDES_CFG, reg_val);

	/* restore the linkrate */
	reg_val = hisi_sas_phy_read32(hisi_hba, phy_id, PROG_PHY_LINK_RATE);
	/* init OOB link rate as 1.5 Gbits */
	reg_val &= ~CFG_PROG_PHY_LINK_RATE_MSK;
	reg_val |= (0x8 << CFG_PROG_PHY_LINK_RATE_OFF);
	hisi_sas_phy_write32(hisi_hba, phy_id, PROG_PHY_LINK_RATE, reg_val);

	/* enable PHY */
	hisi_sas_phy_enable(hisi_hba, phy_id, 1);
}