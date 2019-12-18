#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* shost; } ;
struct sas_ha_struct {int num_phys; int /*<<< orphan*/  sas_addr; TYPE_2__ core; struct asd_sas_phy** sas_phy; } ;
struct asd_sas_phy {TYPE_4__* phy; int /*<<< orphan*/  tproto; int /*<<< orphan*/  iproto; scalar_t__ frame_rcvd_size; int /*<<< orphan*/  sas_prim_lock; int /*<<< orphan*/  frame_rcvd_lock; struct sas_ha_struct* ha; int /*<<< orphan*/ * port; int /*<<< orphan*/  port_phy_el; int /*<<< orphan*/  event_nr; scalar_t__ error; } ;
struct TYPE_8__ {int phy_identifier; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  target_port_protocols; int /*<<< orphan*/  initiator_port_protocols; } ;
struct TYPE_9__ {void* negotiated_linkrate; void* maximum_linkrate; void* minimum_linkrate; void* maximum_linkrate_hw; void* minimum_linkrate_hw; TYPE_3__ identify; } ;
struct TYPE_6__ {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 void* SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_phy_add (TYPE_4__*) ; 
 TYPE_4__* sas_phy_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int sas_register_phys(struct sas_ha_struct *sas_ha)
{
	int i;

	/* Now register the phys. */
	for (i = 0; i < sas_ha->num_phys; i++) {
		struct asd_sas_phy *phy = sas_ha->sas_phy[i];

		phy->error = 0;
		atomic_set(&phy->event_nr, 0);
		INIT_LIST_HEAD(&phy->port_phy_el);

		phy->port = NULL;
		phy->ha = sas_ha;
		spin_lock_init(&phy->frame_rcvd_lock);
		spin_lock_init(&phy->sas_prim_lock);
		phy->frame_rcvd_size = 0;

		phy->phy = sas_phy_alloc(&sas_ha->core.shost->shost_gendev, i);
		if (!phy->phy)
			return -ENOMEM;

		phy->phy->identify.initiator_port_protocols =
			phy->iproto;
		phy->phy->identify.target_port_protocols = phy->tproto;
		phy->phy->identify.sas_address = SAS_ADDR(sas_ha->sas_addr);
		phy->phy->identify.phy_identifier = i;
		phy->phy->minimum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
		phy->phy->maximum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
		phy->phy->minimum_linkrate = SAS_LINK_RATE_UNKNOWN;
		phy->phy->maximum_linkrate = SAS_LINK_RATE_UNKNOWN;
		phy->phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;

		sas_phy_add(phy->phy);
	}

	return 0;
}