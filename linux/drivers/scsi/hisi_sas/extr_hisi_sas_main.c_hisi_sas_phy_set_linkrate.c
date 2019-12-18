#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_phy_linkrates {scalar_t__ minimum_linkrate; scalar_t__ maximum_linkrate; } ;
struct asd_sas_phy {TYPE_1__* phy; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {TYPE_2__* hw; struct hisi_sas_phy* phy; } ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_set_linkrate ) (struct hisi_hba*,int,struct sas_phy_linkrates*) ;} ;
struct TYPE_3__ {int maximum_linkrate; int minimum_linkrate; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SAS_LINK_RATE_1_5_GBPS ; 
 scalar_t__ SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int,struct sas_phy_linkrates*) ; 

__attribute__((used)) static int hisi_sas_phy_set_linkrate(struct hisi_hba *hisi_hba, int phy_no,
			struct sas_phy_linkrates *r)
{
	struct sas_phy_linkrates _r;

	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	enum sas_linkrate min, max;

	if (r->minimum_linkrate > SAS_LINK_RATE_1_5_GBPS)
		return -EINVAL;

	if (r->maximum_linkrate == SAS_LINK_RATE_UNKNOWN) {
		max = sas_phy->phy->maximum_linkrate;
		min = r->minimum_linkrate;
	} else if (r->minimum_linkrate == SAS_LINK_RATE_UNKNOWN) {
		max = r->maximum_linkrate;
		min = sas_phy->phy->minimum_linkrate;
	} else
		return -EINVAL;

	_r.maximum_linkrate = max;
	_r.minimum_linkrate = min;

	sas_phy->phy->maximum_linkrate = max;
	sas_phy->phy->minimum_linkrate = min;

	hisi_sas_phy_enable(hisi_hba, phy_no, 0);
	msleep(100);
	hisi_hba->hw->phy_set_linkrate(hisi_hba, phy_no, &_r);
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);

	return 0;
}