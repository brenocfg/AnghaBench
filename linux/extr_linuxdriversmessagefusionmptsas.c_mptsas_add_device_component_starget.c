#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int /*<<< orphan*/ * hostdata; TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {TYPE_2__ identify; } ;
struct TYPE_6__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  device_info; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; int /*<<< orphan*/  handle_enclosure; } ;
struct mptsas_phyinfo {TYPE_3__ attached; } ;
struct mptsas_enclosure {int /*<<< orphan*/  enclosure_logical_id; } ;
typedef  int /*<<< orphan*/  VirtTarget ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int MPI_SAS_ENCLOS_PGAD_FORM_HANDLE ; 
 int MPI_SAS_ENCLOS_PGAD_FORM_SHIFT ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mptsas_enclosure*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mptsas_add_device_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mptsas_phyinfo* mptsas_find_phyinfo_by_sas_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptsas_sas_enclosure_pg0 (int /*<<< orphan*/ *,struct mptsas_enclosure*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptsas_add_device_component_starget(MPT_ADAPTER *ioc,
	struct scsi_target *starget)
{
	VirtTarget	*vtarget;
	struct sas_rphy	*rphy;
	struct mptsas_phyinfo	*phy_info = NULL;
	struct mptsas_enclosure	enclosure_info;

	rphy = dev_to_rphy(starget->dev.parent);
	vtarget = starget->hostdata;
	phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
			rphy->identify.sas_address);
	if (!phy_info)
		return;

	memset(&enclosure_info, 0, sizeof(struct mptsas_enclosure));
	mptsas_sas_enclosure_pg0(ioc, &enclosure_info,
		(MPI_SAS_ENCLOS_PGAD_FORM_HANDLE <<
		MPI_SAS_ENCLOS_PGAD_FORM_SHIFT),
		phy_info->attached.handle_enclosure);

	mptsas_add_device_component(ioc, phy_info->attached.channel,
		phy_info->attached.id, phy_info->attached.sas_address,
		phy_info->attached.device_info,
		phy_info->attached.slot, enclosure_info.enclosure_logical_id);
}