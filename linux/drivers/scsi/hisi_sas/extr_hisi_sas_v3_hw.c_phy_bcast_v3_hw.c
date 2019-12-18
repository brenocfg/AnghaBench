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
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;} ;
struct asd_sas_phy {int dummy; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {int /*<<< orphan*/  flags; struct sas_ha_struct sha; struct hisi_sas_phy* phy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHL_INT0 ; 
 int CHL_INT0_SL_RX_BCST_ACK_MSK ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 int RX_BCAST_CHG_MSK ; 
 int /*<<< orphan*/  RX_PRIMS_STATUS ; 
 int /*<<< orphan*/  SL_RX_BCAST_CHK_MSK ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t phy_bcast_v3_hw(int phy_no, struct hisi_hba *hisi_hba)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_ha_struct *sas_ha = &hisi_hba->sha;
	u32 bcast_status;

	hisi_sas_phy_write32(hisi_hba, phy_no, SL_RX_BCAST_CHK_MSK, 1);
	bcast_status = hisi_sas_phy_read32(hisi_hba, phy_no, RX_PRIMS_STATUS);
	if ((bcast_status & RX_BCAST_CHG_MSK) &&
	    !test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		sas_ha->notify_port_event(sas_phy, PORTE_BROADCAST_RCVD);
	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0,
			     CHL_INT0_SL_RX_BCST_ACK_MSK);
	hisi_sas_phy_write32(hisi_hba, phy_no, SL_RX_BCAST_CHK_MSK, 0);

	return IRQ_HANDLED;
}