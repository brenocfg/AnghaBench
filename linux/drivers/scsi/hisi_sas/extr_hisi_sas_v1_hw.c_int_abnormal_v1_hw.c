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
struct asd_sas_phy {int id; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHL_INT0 ; 
 int CHL_INT0_DWS_LOST_MSK ; 
 int CHL_INT0_ID_TIMEOUT_MSK ; 
 int /*<<< orphan*/  CHL_INT0_MSK ; 
 int CHL_INT0_MSK_PHYCTRL_NOTRDY_MSK ; 
 int CHL_INT0_PHYCTRL_NOTRDY_MSK ; 
 int CHL_INT0_SL_IDAF_FAIL_MSK ; 
 int CHL_INT0_SL_OPAF_FAIL_MSK ; 
 int CHL_INT0_SL_PS_FAIL_OFF ; 
 int CHL_INT0_SN_FAIL_NGR_MSK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PHY_STATE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  hisi_sas_phy_down (struct hisi_hba*,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t int_abnormal_v1_hw(int irq, void *p)
{
	struct hisi_sas_phy *phy = p;
	struct hisi_hba *hisi_hba = phy->hisi_hba;
	struct device *dev = hisi_hba->dev;
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	u32 irq_value, irq_mask_old;
	int phy_no = sas_phy->id;

	/* mask_int0 */
	irq_mask_old = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT0_MSK);
	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0_MSK, 0x3fffff);

	/* read int0 */
	irq_value = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT0);

	if (irq_value & CHL_INT0_PHYCTRL_NOTRDY_MSK) {
		u32 phy_state = hisi_sas_read32(hisi_hba, PHY_STATE);

		hisi_sas_phy_down(hisi_hba, phy_no,
				  (phy_state & 1 << phy_no) ? 1 : 0);
	}

	if (irq_value & CHL_INT0_ID_TIMEOUT_MSK)
		dev_dbg(dev, "abnormal: ID_TIMEOUT phy%d identify timeout\n",
			phy_no);

	if (irq_value & CHL_INT0_DWS_LOST_MSK)
		dev_dbg(dev, "abnormal: DWS_LOST phy%d dws lost\n", phy_no);

	if (irq_value & CHL_INT0_SN_FAIL_NGR_MSK)
		dev_dbg(dev, "abnormal: SN_FAIL_NGR phy%d sn fail ngr\n",
			phy_no);

	if (irq_value & CHL_INT0_SL_IDAF_FAIL_MSK ||
		irq_value & CHL_INT0_SL_OPAF_FAIL_MSK)
		dev_dbg(dev, "abnormal: SL_ID/OPAF_FAIL phy%d check adr frm err\n",
			phy_no);

	if (irq_value & CHL_INT0_SL_PS_FAIL_OFF)
		dev_dbg(dev, "abnormal: SL_PS_FAIL phy%d fail\n", phy_no);

	/* write to zero */
	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0, irq_value);

	if (irq_value & CHL_INT0_PHYCTRL_NOTRDY_MSK)
		hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0_MSK,
				0x3fffff & ~CHL_INT0_MSK_PHYCTRL_NOTRDY_MSK);
	else
		hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0_MSK,
				irq_mask_old);

	return IRQ_HANDLED;
}