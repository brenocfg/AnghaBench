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
struct hisi_hba {int debugfs_bist_linkrate; int debugfs_bist_phy_no; int debugfs_bist_code_mode; int debugfs_bist_mode; int debugfs_bist_cnt; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CFG_BIST_MODE_SEL_MSK ; 
 int CFG_BIST_MODE_SEL_OFF ; 
 int CFG_BIST_TEST_MSK ; 
 int CFG_LOOP_TEST_MODE_MSK ; 
 int CFG_LOOP_TEST_MODE_OFF ; 
 int CFG_PROG_PHY_LINK_RATE_MSK ; 
 int CFG_PROG_PHY_LINK_RATE_OFF ; 
 int CFG_RX_BIST_EN_MSK ; 
 int CFG_TX_BIST_EN_MSK ; 
 int /*<<< orphan*/  PROG_PHY_LINK_RATE ; 
 int /*<<< orphan*/  SAS_BIST_ERR_CNT ; 
 int /*<<< orphan*/  SAS_PHY_BIST_CODE ; 
 int /*<<< orphan*/  SAS_PHY_BIST_CODE1 ; 
 int SAS_PHY_BIST_CODE1_INIT ; 
 int SAS_PHY_BIST_CODE_INIT ; 
 int /*<<< orphan*/  SAS_PHY_BIST_CTRL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  hisi_sas_bist_test_prep_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_bist_test_restore_v3_hw (struct hisi_hba*) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int debugfs_set_bist_v3_hw(struct hisi_hba *hisi_hba, bool enable)
{
	u32 reg_val, mode_tmp;
	u32 linkrate = hisi_hba->debugfs_bist_linkrate;
	u32 phy_id = hisi_hba->debugfs_bist_phy_no;
	u32 code_mode = hisi_hba->debugfs_bist_code_mode;
	u32 path_mode = hisi_hba->debugfs_bist_mode;
	struct device *dev = hisi_hba->dev;

	dev_info(dev, "BIST info:linkrate=%d phy_id=%d code_mode=%d path_mode=%d\n",
		 linkrate, phy_id, code_mode, path_mode);
	mode_tmp = path_mode ? 2 : 1;
	if (enable) {
		/* some preparations before bist test */
		hisi_sas_bist_test_prep_v3_hw(hisi_hba);

		/* set linkrate of bit test*/
		reg_val = hisi_sas_phy_read32(hisi_hba, phy_id,
					      PROG_PHY_LINK_RATE);
		reg_val &= ~CFG_PROG_PHY_LINK_RATE_MSK;
		reg_val |= (linkrate << CFG_PROG_PHY_LINK_RATE_OFF);
		hisi_sas_phy_write32(hisi_hba, phy_id,
				     PROG_PHY_LINK_RATE, reg_val);

		/* set code mode of bit test */
		reg_val = hisi_sas_phy_read32(hisi_hba, phy_id,
					      SAS_PHY_BIST_CTRL);
		reg_val &= ~(CFG_BIST_MODE_SEL_MSK |
				CFG_LOOP_TEST_MODE_MSK |
				CFG_RX_BIST_EN_MSK |
				CFG_TX_BIST_EN_MSK |
				CFG_BIST_TEST_MSK);
		reg_val |= ((code_mode << CFG_BIST_MODE_SEL_OFF) |
			    (mode_tmp << CFG_LOOP_TEST_MODE_OFF) |
			    CFG_BIST_TEST_MSK);
		hisi_sas_phy_write32(hisi_hba, phy_id,
				     SAS_PHY_BIST_CTRL, reg_val);

		mdelay(100);
		reg_val |= (CFG_RX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK);
		hisi_sas_phy_write32(hisi_hba, phy_id,
				     SAS_PHY_BIST_CTRL, reg_val);

		/* set the bist init value */
		hisi_sas_phy_write32(hisi_hba, phy_id,
				     SAS_PHY_BIST_CODE,
				     SAS_PHY_BIST_CODE_INIT);
		hisi_sas_phy_write32(hisi_hba, phy_id,
				     SAS_PHY_BIST_CODE1,
				     SAS_PHY_BIST_CODE1_INIT);

		/* clear error bit */
		mdelay(100);
		hisi_sas_phy_read32(hisi_hba, phy_id, SAS_BIST_ERR_CNT);
	} else {
		/* disable bist test and recover it */
		hisi_hba->debugfs_bist_cnt += hisi_sas_phy_read32(hisi_hba,
				phy_id, SAS_BIST_ERR_CNT);
		hisi_sas_bist_test_restore_v3_hw(hisi_hba);
	}

	return 0;
}