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
struct asd_sas_phy {TYPE_1__* phy; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {int n_phy; struct hisi_sas_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int) ; 

__attribute__((used)) static void phys_init_v3_hw(struct hisi_hba *hisi_hba)
{
	int i;

	for (i = 0; i < hisi_hba->n_phy; i++) {
		struct hisi_sas_phy *phy = &hisi_hba->phy[i];
		struct asd_sas_phy *sas_phy = &phy->sas_phy;

		if (!sas_phy->phy->enabled)
			continue;

		hisi_sas_phy_enable(hisi_hba, i, 1);
	}
}