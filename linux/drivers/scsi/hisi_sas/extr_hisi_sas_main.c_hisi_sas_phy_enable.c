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
struct sas_phy {int /*<<< orphan*/  negotiated_linkrate; } ;
struct asd_sas_phy {struct sas_phy* phy; } ;
struct hisi_sas_phy {int enable; int /*<<< orphan*/  lock; struct asd_sas_phy sas_phy; } ;
struct hisi_hba {TYPE_1__* hw; struct hisi_sas_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_disable ) (struct hisi_hba*,int) ;int /*<<< orphan*/  (* phy_start ) (struct hisi_hba*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PHY_DISABLED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  stub2 (struct hisi_hba*,int) ; 

void hisi_sas_phy_enable(struct hisi_hba *hisi_hba, int phy_no, int enable)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *aphy = &phy->sas_phy;
	struct sas_phy *sphy = aphy->phy;
	unsigned long flags;

	spin_lock_irqsave(&phy->lock, flags);

	if (enable) {
		/* We may have been enabled already; if so, don't touch */
		if (!phy->enable)
			sphy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;
		hisi_hba->hw->phy_start(hisi_hba, phy_no);
	} else {
		sphy->negotiated_linkrate = SAS_PHY_DISABLED;
		hisi_hba->hw->phy_disable(hisi_hba, phy_no);
	}
	phy->enable = enable;
	spin_unlock_irqrestore(&phy->lock, flags);
}