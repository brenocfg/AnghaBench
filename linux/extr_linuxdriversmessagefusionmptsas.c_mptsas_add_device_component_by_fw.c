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
typedef  int u8 ;
struct mptsas_enclosure {int /*<<< orphan*/  enclosure_logical_id; } ;
struct mptsas_devinfo {int /*<<< orphan*/  slot; int /*<<< orphan*/  device_info; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; int /*<<< orphan*/  handle_enclosure; } ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID ; 
 int MPI_SAS_DEVICE_PGAD_FORM_SHIFT ; 
 int MPI_SAS_ENCLOS_PGAD_FORM_HANDLE ; 
 int MPI_SAS_ENCLOS_PGAD_FORM_SHIFT ; 
 int /*<<< orphan*/  memset (struct mptsas_enclosure*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mptsas_add_device_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mptsas_sas_device_pg0 (int /*<<< orphan*/ *,struct mptsas_devinfo*,int,int) ; 
 int /*<<< orphan*/  mptsas_sas_enclosure_pg0 (int /*<<< orphan*/ *,struct mptsas_enclosure*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptsas_add_device_component_by_fw(MPT_ADAPTER *ioc, u8 channel, u8 id)
{
	struct mptsas_devinfo sas_device;
	struct mptsas_enclosure enclosure_info;
	int rc;

	rc = mptsas_sas_device_pg0(ioc, &sas_device,
	    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
	     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
	    (channel << 8) + id);
	if (rc)
		return;

	memset(&enclosure_info, 0, sizeof(struct mptsas_enclosure));
	mptsas_sas_enclosure_pg0(ioc, &enclosure_info,
	    (MPI_SAS_ENCLOS_PGAD_FORM_HANDLE <<
	     MPI_SAS_ENCLOS_PGAD_FORM_SHIFT),
	     sas_device.handle_enclosure);

	mptsas_add_device_component(ioc, sas_device.channel,
	    sas_device.id, sas_device.sas_address, sas_device.device_info,
	    sas_device.slot, enclosure_info.enclosure_logical_id);
}