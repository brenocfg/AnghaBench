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
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {scalar_t__ chip_id; TYPE_1__* chip; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_start_req ) (struct pm8001_hba_info*,int) ;int /*<<< orphan*/  (* sas_re_init_req ) (struct pm8001_hba_info*) ;} ;
struct TYPE_3__ {int n_phy; } ;

/* Variables and functions */
 TYPE_2__* PM8001_CHIP_DISP ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 scalar_t__ chip_8001 ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  stub2 (struct pm8001_hba_info*,int) ; 

void pm8001_scan_start(struct Scsi_Host *shost)
{
	int i;
	struct pm8001_hba_info *pm8001_ha;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	pm8001_ha = sha->lldd_ha;
	/* SAS_RE_INITIALIZATION not available in SPCv/ve */
	if (pm8001_ha->chip_id == chip_8001)
		PM8001_CHIP_DISP->sas_re_init_req(pm8001_ha);
	for (i = 0; i < pm8001_ha->chip->n_phy; ++i)
		PM8001_CHIP_DISP->phy_start_req(pm8001_ha, i);
}