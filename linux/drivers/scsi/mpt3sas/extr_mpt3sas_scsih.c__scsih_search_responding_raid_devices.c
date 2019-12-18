#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pd_handles; int /*<<< orphan*/  pd_handles_sz; int /*<<< orphan*/  is_warpdrive; int /*<<< orphan*/  raid_device_list; int /*<<< orphan*/  ir_firmware; } ;
struct TYPE_14__ {int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_13__ {int PhysDiskNum; int /*<<< orphan*/  DevHandle; } ;
struct TYPE_12__ {scalar_t__ VolumeState; } ;
struct TYPE_11__ {int /*<<< orphan*/  WWID; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi2RaidVolPage1_t ;
typedef  TYPE_2__ Mpi2RaidVolPage0_t ;
typedef  TYPE_3__ Mpi2RaidPhysDiskPage0_t ;
typedef  TYPE_4__ Mpi2ConfigReply_t ;

/* Variables and functions */
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM ; 
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE ; 
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_HANDLE ; 
 scalar_t__ MPI2_RAID_VOL_STATE_DEGRADED ; 
 scalar_t__ MPI2_RAID_VOL_STATE_ONLINE ; 
 scalar_t__ MPI2_RAID_VOL_STATE_OPTIMAL ; 
 int /*<<< orphan*/  _scsih_mark_responding_raid_device (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_config_get_phys_disk_pg0 (struct MPT3SAS_ADAPTER*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt3sas_config_get_raid_volume_pg0 (struct MPT3SAS_ADAPTER*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mpt3sas_config_get_raid_volume_pg1 (struct MPT3SAS_ADAPTER*,TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_search_responding_raid_devices(struct MPT3SAS_ADAPTER *ioc)
{
	Mpi2RaidVolPage1_t volume_pg1;
	Mpi2RaidVolPage0_t volume_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 handle;
	u8 phys_disk_num;

	if (!ioc->ir_firmware)
		return;

	ioc_info(ioc, "search for raid volumes: start\n");

	if (list_empty(&ioc->raid_device_list))
		goto out;

	handle = 0xFFFF;
	while (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &volume_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			break;
		handle = le16_to_cpu(volume_pg1.DevHandle);

		if (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply,
		    &volume_pg0, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
		     sizeof(Mpi2RaidVolPage0_t)))
			continue;

		if (volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_OPTIMAL ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_ONLINE ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_DEGRADED)
			_scsih_mark_responding_raid_device(ioc,
			    le64_to_cpu(volume_pg1.WWID), handle);
	}

	/* refresh the pd_handles */
	if (!ioc->is_warpdrive) {
		phys_disk_num = 0xFF;
		memset(ioc->pd_handles, 0, ioc->pd_handles_sz);
		while (!(mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
		    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM,
		    phys_disk_num))) {
			ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
			    MPI2_IOCSTATUS_MASK;
			if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
				break;
			phys_disk_num = pd_pg0.PhysDiskNum;
			handle = le16_to_cpu(pd_pg0.DevHandle);
			set_bit(handle, ioc->pd_handles);
		}
	}
 out:
	ioc_info(ioc, "search for responding raid volumes: complete\n");
}