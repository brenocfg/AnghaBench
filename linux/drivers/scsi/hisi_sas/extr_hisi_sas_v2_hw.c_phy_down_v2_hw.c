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
struct hisi_sas_port {int /*<<< orphan*/  id; } ;
struct hisi_sas_phy {int /*<<< orphan*/  timer; struct hisi_sas_port* port; } ;
struct hisi_hba {int /*<<< orphan*/  timer; struct device* dev; struct hisi_sas_phy* phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHL_INT0 ; 
 int CHL_INT0_NOT_RDY_MSK ; 
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  PHYCTRL_NOT_RDY_MSK ; 
 int /*<<< orphan*/  PHY_STATE ; 
 int /*<<< orphan*/  SL_CONTROL ; 
 int SL_CONTROL_CTA_MSK ; 
 int /*<<< orphan*/  TXID_AUTO ; 
 int TXID_AUTO_CT3_MSK ; 
 int /*<<< orphan*/  check_any_wideports_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  get_wideport_bitmap_v2_hw (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_down (struct hisi_hba*,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phy_down_v2_hw(int phy_no, struct hisi_hba *hisi_hba)
{
	u32 phy_state, sl_ctrl, txid_auto;
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct hisi_sas_port *port = phy->port;
	struct device *dev = hisi_hba->dev;

	del_timer(&phy->timer);
	hisi_sas_phy_write32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 1);

	phy_state = hisi_sas_read32(hisi_hba, PHY_STATE);
	dev_info(dev, "phydown: phy%d phy_state=0x%x\n", phy_no, phy_state);
	hisi_sas_phy_down(hisi_hba, phy_no, (phy_state & 1 << phy_no) ? 1 : 0);

	sl_ctrl = hisi_sas_phy_read32(hisi_hba, phy_no, SL_CONTROL);
	hisi_sas_phy_write32(hisi_hba, phy_no, SL_CONTROL,
			     sl_ctrl & ~SL_CONTROL_CTA_MSK);
	if (port && !get_wideport_bitmap_v2_hw(hisi_hba, port->id))
		if (!check_any_wideports_v2_hw(hisi_hba) &&
				timer_pending(&hisi_hba->timer))
			del_timer(&hisi_hba->timer);

	txid_auto = hisi_sas_phy_read32(hisi_hba, phy_no, TXID_AUTO);
	hisi_sas_phy_write32(hisi_hba, phy_no, TXID_AUTO,
			     txid_auto | TXID_AUTO_CT3_MSK);

	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0, CHL_INT0_NOT_RDY_MSK);
	hisi_sas_phy_write32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 0);

	return IRQ_HANDLED;
}