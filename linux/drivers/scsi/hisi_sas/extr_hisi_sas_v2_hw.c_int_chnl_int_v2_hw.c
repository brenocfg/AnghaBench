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
struct hisi_sas_phy {int dummy; } ;
struct hisi_sas_hw_error {int irq_msk; int /*<<< orphan*/  msg; } ;
struct hisi_hba {struct hisi_sas_phy* phy; int /*<<< orphan*/  rst_work; int /*<<< orphan*/  wq; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct hisi_sas_hw_error*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHL_INT0 ; 
 int CHL_INT0_HOTPLUG_TOUT_MSK ; 
 int CHL_INT0_NOT_RDY_MSK ; 
 int CHL_INT0_PHY_RDY_MSK ; 
 int CHL_INT0_SL_PHY_ENABLE_MSK ; 
 int CHL_INT0_SL_RX_BCST_ACK_MSK ; 
 int /*<<< orphan*/  CHL_INT1 ; 
 int /*<<< orphan*/  CHL_INT2 ; 
 int /*<<< orphan*/  CHL_INT2_SL_IDAF_TOUT_CONF_OFF ; 
 int /*<<< orphan*/  ENT_INT_SRC_MSK3 ; 
 int ENT_INT_SRC_MSK3_ENT95_MSK_MSK ; 
 int /*<<< orphan*/  HGC_INVLD_DQE_INFO ; 
 int HGC_INVLD_DQE_INFO_FB_CH3_OFF ; 
 int /*<<< orphan*/  HISI_PHYE_LINK_RESET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hisi_sas_notify_phy_event (struct hisi_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_oob_ready (struct hisi_hba*,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_bcast_v2_hw (int,struct hisi_hba*) ; 
 struct hisi_sas_hw_error* port_ecc_axi_error ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t int_chnl_int_v2_hw(int irq_no, void *p)
{
	struct hisi_hba *hisi_hba = p;
	struct device *dev = hisi_hba->dev;
	u32 ent_msk, ent_tmp, irq_msk;
	int phy_no = 0;

	ent_msk = hisi_sas_read32(hisi_hba, ENT_INT_SRC_MSK3);
	ent_tmp = ent_msk;
	ent_msk |= ENT_INT_SRC_MSK3_ENT95_MSK_MSK;
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, ent_msk);

	irq_msk = (hisi_sas_read32(hisi_hba, HGC_INVLD_DQE_INFO) >>
			HGC_INVLD_DQE_INFO_FB_CH3_OFF) & 0x1ff;

	while (irq_msk) {
		u32 irq_value0 = hisi_sas_phy_read32(hisi_hba, phy_no,
						     CHL_INT0);
		u32 irq_value1 = hisi_sas_phy_read32(hisi_hba, phy_no,
						     CHL_INT1);
		u32 irq_value2 = hisi_sas_phy_read32(hisi_hba, phy_no,
						     CHL_INT2);

		if ((irq_msk & (1 << phy_no)) && irq_value1) {
			int i;

			for (i = 0; i < ARRAY_SIZE(port_ecc_axi_error); i++) {
				const struct hisi_sas_hw_error *error =
						&port_ecc_axi_error[i];

				if (!(irq_value1 & error->irq_msk))
					continue;

				dev_warn(dev, "%s error (phy%d 0x%x) found!\n",
					error->msg, phy_no, irq_value1);
				queue_work(hisi_hba->wq, &hisi_hba->rst_work);
			}

			hisi_sas_phy_write32(hisi_hba, phy_no,
					     CHL_INT1, irq_value1);
		}

		if ((irq_msk & (1 << phy_no)) && irq_value2) {
			struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];

			if (irq_value2 & BIT(CHL_INT2_SL_IDAF_TOUT_CONF_OFF)) {
				dev_warn(dev, "phy%d identify timeout\n",
					 phy_no);
				hisi_sas_notify_phy_event(phy,
						HISI_PHYE_LINK_RESET);
			}

			hisi_sas_phy_write32(hisi_hba, phy_no,
						 CHL_INT2, irq_value2);
		}

		if ((irq_msk & (1 << phy_no)) && irq_value0) {
			if (irq_value0 & CHL_INT0_SL_RX_BCST_ACK_MSK)
				phy_bcast_v2_hw(phy_no, hisi_hba);

			if (irq_value0 & CHL_INT0_PHY_RDY_MSK)
				hisi_sas_phy_oob_ready(hisi_hba, phy_no);

			hisi_sas_phy_write32(hisi_hba, phy_no,
					CHL_INT0, irq_value0
					& (~CHL_INT0_HOTPLUG_TOUT_MSK)
					& (~CHL_INT0_SL_PHY_ENABLE_MSK)
					& (~CHL_INT0_NOT_RDY_MSK));
		}
		irq_msk &= ~(1 << phy_no);
		phy_no++;
	}

	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, ent_tmp);

	return IRQ_HANDLED;
}