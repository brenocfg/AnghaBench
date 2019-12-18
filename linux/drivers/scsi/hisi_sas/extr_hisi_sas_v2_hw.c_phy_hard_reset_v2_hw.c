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
struct TYPE_2__ {scalar_t__ device_type; } ;
struct hisi_sas_phy {TYPE_1__ identify; } ;
struct hisi_hba {struct hisi_sas_phy* phy; } ;

/* Variables and functions */
 scalar_t__ SAS_END_DEVICE ; 
 int /*<<< orphan*/  TXID_AUTO ; 
 int TX_HARDRST_MSK ; 
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void phy_hard_reset_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 txid_auto;

	hisi_sas_phy_enable(hisi_hba, phy_no, 0);
	if (phy->identify.device_type == SAS_END_DEVICE) {
		txid_auto = hisi_sas_phy_read32(hisi_hba, phy_no, TXID_AUTO);
		hisi_sas_phy_write32(hisi_hba, phy_no, TXID_AUTO,
					txid_auto | TX_HARDRST_MSK);
	}
	msleep(100);
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);
}