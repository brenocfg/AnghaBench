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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_hba {int debugfs_bist_phy_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_ALOS_CHK_DISABLE_MSK ; 
 int /*<<< orphan*/  SERDES_CFG ; 
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_sas_bist_test_prep_v3_hw(struct hisi_hba *hisi_hba)
{
	u32 reg_val;
	int phy_id = hisi_hba->debugfs_bist_phy_no;

	/* disable PHY */
	hisi_sas_phy_enable(hisi_hba, phy_id, 0);

	/* disable ALOS */
	reg_val = hisi_sas_phy_read32(hisi_hba, phy_id, SERDES_CFG);
	reg_val |= CFG_ALOS_CHK_DISABLE_MSK;
	hisi_sas_phy_write32(hisi_hba, phy_id, SERDES_CFG, reg_val);
}