#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct _sas_node {int dummy; } ;
struct _sas_device {int dummy; } ;
struct _raid_device {int dummy; } ;
struct _pcie_device {int dummy; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  raid_device_lock; int /*<<< orphan*/  pd_handles; int /*<<< orphan*/  ir_firmware; int /*<<< orphan*/  sas_node_lock; } ;
struct TYPE_30__ {int /*<<< orphan*/  WWID; int /*<<< orphan*/  ParentDevHandle; int /*<<< orphan*/  DeviceInfo; int /*<<< orphan*/  DevHandle; } ;
struct TYPE_29__ {int /*<<< orphan*/  IOCLogInfo; int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_28__ {int /*<<< orphan*/  VolDevHandle; int /*<<< orphan*/  ReasonCode; } ;
struct TYPE_27__ {int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  DevHandle; } ;
struct TYPE_26__ {int PhysDiskNum; int /*<<< orphan*/  DevHandle; } ;
struct TYPE_25__ {scalar_t__ VolumeState; } ;
struct TYPE_24__ {int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  WWID; } ;
struct TYPE_23__ {int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  PhyNum; int /*<<< orphan*/  ParentDevHandle; int /*<<< orphan*/  DeviceInfo; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi2SasDevicePage0_t ;
typedef  TYPE_2__ Mpi2RaidVolPage1_t ;
typedef  TYPE_3__ Mpi2RaidVolPage0_t ;
typedef  TYPE_4__ Mpi2RaidPhysDiskPage0_t ;
typedef  TYPE_5__ Mpi2ExpanderPage0_t ;
typedef  TYPE_6__ Mpi2EventIrConfigElement_t ;
typedef  TYPE_7__ Mpi2ConfigReply_t ;
typedef  TYPE_8__ Mpi26PCIeDevicePage0_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI26_PCIE_DEVICE_PGAD_FORM_GET_NEXT_HANDLE ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_CHANGE_RC_ADDED ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM ; 
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE ; 
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_HANDLE ; 
 scalar_t__ MPI2_RAID_VOL_STATE_DEGRADED ; 
 scalar_t__ MPI2_RAID_VOL_STATE_ONLINE ; 
 scalar_t__ MPI2_RAID_VOL_STATE_OPTIMAL ; 
 int /*<<< orphan*/  MPI2_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE ; 
 int /*<<< orphan*/  MPI2_SAS_DEVICE_PGAD_FORM_HANDLE ; 
 int /*<<< orphan*/  MPI2_SAS_EXPAND_PGAD_FORM_GET_NEXT_HNDL ; 
 int /*<<< orphan*/  MPI2_SAS_NEG_LINK_RATE_1_5 ; 
 scalar_t__ _scsih_add_device (struct MPT3SAS_ADAPTER*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _scsih_expander_add (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  _scsih_get_sas_address (struct MPT3SAS_ADAPTER*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _scsih_is_end_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_is_nvme_pciescsi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_pcie_add_device (struct MPT3SAS_ADAPTER*,int) ; 
 struct _raid_device* _scsih_raid_device_find_by_wwid (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  _scsih_refresh_expander_links (struct MPT3SAS_ADAPTER*,struct _sas_node*,int) ; 
 int /*<<< orphan*/  _scsih_sas_host_refresh (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_sas_volume_add (struct MPT3SAS_ADAPTER*,TYPE_6__*) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt3sas_config_get_expander_pg0 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt3sas_config_get_pcie_device_pg0 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt3sas_config_get_phys_disk_pg0 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt3sas_config_get_raid_volume_pg0 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mpt3sas_config_get_raid_volume_pg1 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt3sas_config_get_sas_device_pg0 (struct MPT3SAS_ADAPTER*,TYPE_7__*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct _pcie_device* mpt3sas_get_pdev_by_wwid (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 struct _sas_device* mpt3sas_get_sdev_by_addr (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 struct _sas_device* mpt3sas_get_sdev_by_handle (struct MPT3SAS_ADAPTER*,int) ; 
 struct _sas_node* mpt3sas_scsih_expander_find_by_sas_address (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  mpt3sas_transport_update_links (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static void
_scsih_scan_for_devices_after_reset(struct MPT3SAS_ADAPTER *ioc)
{
	Mpi2ExpanderPage0_t expander_pg0;
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	Mpi2RaidVolPage1_t volume_pg1;
	Mpi2RaidVolPage0_t volume_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2EventIrConfigElement_t element;
	Mpi2ConfigReply_t mpi_reply;
	u8 phys_disk_num;
	u16 ioc_status;
	u16 handle, parent_handle;
	u64 sas_address;
	struct _sas_device *sas_device;
	struct _pcie_device *pcie_device;
	struct _sas_node *expander_device;
	static struct _raid_device *raid_device;
	u8 retry_count;
	unsigned long flags;

	ioc_info(ioc, "scan devices: start\n");

	_scsih_sas_host_refresh(ioc);

	ioc_info(ioc, "\tscan devices: expanders start\n");

	/* expanders */
	handle = 0xFFFF;
	while (!(mpt3sas_config_get_expander_pg0(ioc, &mpi_reply, &expander_pg0,
	    MPI2_SAS_EXPAND_PGAD_FORM_GET_NEXT_HNDL, handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from expander scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		handle = le16_to_cpu(expander_pg0.DevHandle);
		spin_lock_irqsave(&ioc->sas_node_lock, flags);
		expander_device = mpt3sas_scsih_expander_find_by_sas_address(
		    ioc, le64_to_cpu(expander_pg0.SASAddress));
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		if (expander_device)
			_scsih_refresh_expander_links(ioc, expander_device,
			    handle);
		else {
			ioc_info(ioc, "\tBEFORE adding expander: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(expander_pg0.SASAddress));
			_scsih_expander_add(ioc, handle);
			ioc_info(ioc, "\tAFTER adding expander: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(expander_pg0.SASAddress));
		}
	}

	ioc_info(ioc, "\tscan devices: expanders complete\n");

	if (!ioc->ir_firmware)
		goto skip_to_sas;

	ioc_info(ioc, "\tscan devices: phys disk start\n");

	/* phys disk */
	phys_disk_num = 0xFF;
	while (!(mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
	    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM,
	    phys_disk_num))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from phys disk scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		phys_disk_num = pd_pg0.PhysDiskNum;
		handle = le16_to_cpu(pd_pg0.DevHandle);
		sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
		if (sas_device) {
			sas_device_put(sas_device);
			continue;
		}
		if (mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
		    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_HANDLE,
		    handle) != 0)
			continue;
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from phys disk scan ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
		if (!_scsih_get_sas_address(ioc, parent_handle,
		    &sas_address)) {
			ioc_info(ioc, "\tBEFORE adding phys disk: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
			mpt3sas_transport_update_links(ioc, sas_address,
			    handle, sas_device_pg0.PhyNum,
			    MPI2_SAS_NEG_LINK_RATE_1_5);
			set_bit(handle, ioc->pd_handles);
			retry_count = 0;
			/* This will retry adding the end device.
			 * _scsih_add_device() will decide on retries and
			 * return "1" when it should be retried
			 */
			while (_scsih_add_device(ioc, handle, retry_count++,
			    1)) {
				ssleep(1);
			}
			ioc_info(ioc, "\tAFTER adding phys disk: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
		}
	}

	ioc_info(ioc, "\tscan devices: phys disk complete\n");

	ioc_info(ioc, "\tscan devices: volumes start\n");

	/* volumes */
	handle = 0xFFFF;
	while (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &volume_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from volume scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		handle = le16_to_cpu(volume_pg1.DevHandle);
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_wwid(ioc,
		    le64_to_cpu(volume_pg1.WWID));
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		if (raid_device)
			continue;
		if (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply,
		    &volume_pg0, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
		     sizeof(Mpi2RaidVolPage0_t)))
			continue;
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from volume scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		if (volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_OPTIMAL ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_ONLINE ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_DEGRADED) {
			memset(&element, 0, sizeof(Mpi2EventIrConfigElement_t));
			element.ReasonCode = MPI2_EVENT_IR_CHANGE_RC_ADDED;
			element.VolDevHandle = volume_pg1.DevHandle;
			ioc_info(ioc, "\tBEFORE adding volume: handle (0x%04x)\n",
				 volume_pg1.DevHandle);
			_scsih_sas_volume_add(ioc, &element);
			ioc_info(ioc, "\tAFTER adding volume: handle (0x%04x)\n",
				 volume_pg1.DevHandle);
		}
	}

	ioc_info(ioc, "\tscan devices: volumes complete\n");

 skip_to_sas:

	ioc_info(ioc, "\tscan devices: end devices start\n");

	/* sas devices */
	handle = 0xFFFF;
	while (!(mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
	    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
	    handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from end device scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		handle = le16_to_cpu(sas_device_pg0.DevHandle);
		if (!(_scsih_is_end_device(
		    le32_to_cpu(sas_device_pg0.DeviceInfo))))
			continue;
		sas_device = mpt3sas_get_sdev_by_addr(ioc,
		    le64_to_cpu(sas_device_pg0.SASAddress));
		if (sas_device) {
			sas_device_put(sas_device);
			continue;
		}
		parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
		if (!_scsih_get_sas_address(ioc, parent_handle, &sas_address)) {
			ioc_info(ioc, "\tBEFORE adding end device: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
			mpt3sas_transport_update_links(ioc, sas_address, handle,
			    sas_device_pg0.PhyNum, MPI2_SAS_NEG_LINK_RATE_1_5);
			retry_count = 0;
			/* This will retry adding the end device.
			 * _scsih_add_device() will decide on retries and
			 * return "1" when it should be retried
			 */
			while (_scsih_add_device(ioc, handle, retry_count++,
			    0)) {
				ssleep(1);
			}
			ioc_info(ioc, "\tAFTER adding end device: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
		}
	}
	ioc_info(ioc, "\tscan devices: end devices complete\n");
	ioc_info(ioc, "\tscan devices: pcie end devices start\n");

	/* pcie devices */
	handle = 0xFFFF;
	while (!(mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
		&pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
		handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus)
				& MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS) {
			ioc_info(ioc, "\tbreak from pcie end device scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			break;
		}
		handle = le16_to_cpu(pcie_device_pg0.DevHandle);
		if (!(_scsih_is_nvme_pciescsi_device(
			le32_to_cpu(pcie_device_pg0.DeviceInfo))))
			continue;
		pcie_device = mpt3sas_get_pdev_by_wwid(ioc,
				le64_to_cpu(pcie_device_pg0.WWID));
		if (pcie_device) {
			pcie_device_put(pcie_device);
			continue;
		}
		retry_count = 0;
		parent_handle = le16_to_cpu(pcie_device_pg0.ParentDevHandle);
		_scsih_pcie_add_device(ioc, handle);

		ioc_info(ioc, "\tAFTER adding pcie end device: handle (0x%04x), wwid(0x%016llx)\n",
			 handle, (u64)le64_to_cpu(pcie_device_pg0.WWID));
	}
	ioc_info(ioc, "\tpcie devices: pcie end devices complete\n");
	ioc_info(ioc, "scan devices: complete\n");
}