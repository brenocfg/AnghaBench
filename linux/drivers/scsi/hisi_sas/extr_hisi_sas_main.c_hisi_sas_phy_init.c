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
struct sas_ha_struct {int dummy; } ;
struct asd_sas_phy {int enabled; int id; struct hisi_sas_phy* lldd_phy; struct sas_ha_struct* ha; int /*<<< orphan*/ * frame_rcvd; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  linkrate; int /*<<< orphan*/  oob_mode; int /*<<< orphan*/  role; int /*<<< orphan*/  type; scalar_t__ tproto; int /*<<< orphan*/  iproto; int /*<<< orphan*/  class; } ;
struct hisi_sas_phy {int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * works; int /*<<< orphan*/ * frame_rcvd; int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; int /*<<< orphan*/ * port; struct hisi_hba* hisi_hba; struct asd_sas_phy sas_phy; } ;
struct hisi_hba {int n_phy; TYPE_2__* shost; int /*<<< orphan*/ * sas_addr; TYPE_1__* hw; struct hisi_sas_phy* phy; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_get_max_linkrate ) () ;} ;

/* Variables and functions */
 int HISI_PHYES_NUM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OOB_NOT_CONNECTED ; 
 int /*<<< orphan*/  PHY_ROLE_INITIATOR ; 
 int /*<<< orphan*/  PHY_TYPE_PHYSICAL ; 
 int /*<<< orphan*/  SAS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/ * hisi_sas_phye_fns ; 
 int /*<<< orphan*/  hisi_sas_wait_phyup_timedout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_sas_phy_init(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	int i;

	phy->hisi_hba = hisi_hba;
	phy->port = NULL;
	phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
	phy->maximum_linkrate = hisi_hba->hw->phy_get_max_linkrate();
	sas_phy->enabled = (phy_no < hisi_hba->n_phy) ? 1 : 0;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;
	sas_phy->id = phy_no;
	sas_phy->sas_addr = &hisi_hba->sas_addr[0];
	sas_phy->frame_rcvd = &phy->frame_rcvd[0];
	sas_phy->ha = (struct sas_ha_struct *)hisi_hba->shost->hostdata;
	sas_phy->lldd_phy = phy;

	for (i = 0; i < HISI_PHYES_NUM; i++)
		INIT_WORK(&phy->works[i], hisi_sas_phye_fns[i]);

	spin_lock_init(&phy->lock);

	timer_setup(&phy->timer, hisi_sas_wait_phyup_timedout, 0);
}