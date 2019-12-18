#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sas_rphy {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct sas_phy {size_t number; TYPE_4__ dev; } ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_6__ {TYPE_1__* shost; } ;
struct sas_ha_struct {TYPE_2__ core; struct asd_sas_phy** sas_phy; } ;
struct domain_device {int dummy; } ;
struct asd_sas_phy {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum phy_func { ____Placeholder_phy_func } phy_func ;
struct TYPE_7__ {int (* lldd_control_phy ) (struct asd_sas_phy*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int PHY_FUNC_HARD_RESET ; 
 int PHY_FUNC_LINK_RESET ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_ata_schedule_reset (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ata_wait_eh (struct domain_device*) ; 
 struct domain_device* sas_ex_to_ata (struct domain_device*,size_t) ; 
 struct domain_device* sas_find_dev_by_rphy (struct sas_rphy*) ; 
 int sas_smp_phy_control (struct domain_device*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sas_try_ata_reset (struct asd_sas_phy*) ; 
 scalar_t__ scsi_is_sas_phy_local (struct sas_phy*) ; 
 int stub1 (struct asd_sas_phy*,int,int /*<<< orphan*/ *) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transport_sas_phy_reset(struct sas_phy *phy, int hard_reset)
{
	enum phy_func reset_type;

	if (hard_reset)
		reset_type = PHY_FUNC_HARD_RESET;
	else
		reset_type = PHY_FUNC_LINK_RESET;

	if (scsi_is_sas_phy_local(phy)) {
		struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(shost);
		struct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		struct sas_internal *i =
			to_sas_internal(sas_ha->core.shost->transportt);

		if (!hard_reset && sas_try_ata_reset(asd_phy) == 0)
			return 0;
		return i->dft->lldd_control_phy(asd_phy, reset_type, NULL);
	} else {
		struct sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		struct domain_device *ddev = sas_find_dev_by_rphy(rphy);
		struct domain_device *ata_dev = sas_ex_to_ata(ddev, phy->number);

		if (ata_dev && !hard_reset) {
			sas_ata_schedule_reset(ata_dev);
			sas_ata_wait_eh(ata_dev);
			return 0;
		} else
			return sas_smp_phy_control(ddev, phy->number, reset_type, NULL);
	}
}