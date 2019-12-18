#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  void* u16 ;
struct scsi_target {struct MPT3SAS_TARGET* hostdata; } ;
struct _pcie_device {void* handle; char* connector_name; scalar_t__ enclosure_level; int /*<<< orphan*/  access_status; struct scsi_target* starget; } ;
struct MPT3SAS_TARGET {void* handle; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pcie_device_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  AccessStatus; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * ConnectorName; scalar_t__ EnclosureLevel; int /*<<< orphan*/  WWID; int /*<<< orphan*/  DeviceInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_1__ Mpi2ConfigReply_t ;
typedef  TYPE_2__ Mpi26PCIeDevicePage0_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int MPI26_PCIEDEV0_FLAGS_DEVICE_PRESENT ; 
 int MPI26_PCIEDEV0_FLAGS_ENCL_LEVEL_VALID ; 
 int /*<<< orphan*/  MPI26_PCIE_DEVICE_PGAD_FORM_HANDLE ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 struct _pcie_device* __mpt3sas_get_pdev_by_wwid (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 scalar_t__ _scsih_check_pcie_access_status (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_is_nvme_pciescsi_device (int) ; 
 int /*<<< orphan*/  _scsih_ublock_io_device (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,void*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mpt3sas_config_get_pcie_device_pg0 (struct MPT3SAS_ADAPTER*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,struct scsi_target*,char*,void*,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
_scsih_pcie_check_device(struct MPT3SAS_ADAPTER *ioc, u16 handle)
{
	Mpi2ConfigReply_t mpi_reply;
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	u32 ioc_status;
	struct _pcie_device *pcie_device;
	u64 wwid;
	unsigned long flags;
	struct scsi_target *starget;
	struct MPT3SAS_TARGET *sas_target_priv_data;
	u32 device_info;

	if ((mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
		&pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_HANDLE, handle)))
		return;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		return;

	/* check if this is end device */
	device_info = le32_to_cpu(pcie_device_pg0.DeviceInfo);
	if (!(_scsih_is_nvme_pciescsi_device(device_info)))
		return;

	wwid = le64_to_cpu(pcie_device_pg0.WWID);
	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_wwid(ioc, wwid);

	if (!pcie_device) {
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		return;
	}

	if (unlikely(pcie_device->handle != handle)) {
		starget = pcie_device->starget;
		sas_target_priv_data = starget->hostdata;
		pcie_device->access_status = pcie_device_pg0.AccessStatus;
		starget_printk(KERN_INFO, starget,
		    "handle changed from(0x%04x) to (0x%04x)!!!\n",
		    pcie_device->handle, handle);
		sas_target_priv_data->handle = handle;
		pcie_device->handle = handle;

		if (le32_to_cpu(pcie_device_pg0.Flags) &
		    MPI26_PCIEDEV0_FLAGS_ENCL_LEVEL_VALID) {
			pcie_device->enclosure_level =
			    pcie_device_pg0.EnclosureLevel;
			memcpy(&pcie_device->connector_name[0],
			    &pcie_device_pg0.ConnectorName[0], 4);
		} else {
			pcie_device->enclosure_level = 0;
			pcie_device->connector_name[0] = '\0';
		}
	}

	/* check if device is present */
	if (!(le32_to_cpu(pcie_device_pg0.Flags) &
	    MPI26_PCIEDEV0_FLAGS_DEVICE_PRESENT)) {
		ioc_info(ioc, "device is not present handle(0x%04x), flags!!!\n",
			 handle);
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		pcie_device_put(pcie_device);
		return;
	}

	/* check if there were any issues with discovery */
	if (_scsih_check_pcie_access_status(ioc, wwid, handle,
	    pcie_device_pg0.AccessStatus)) {
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		pcie_device_put(pcie_device);
		return;
	}

	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	pcie_device_put(pcie_device);

	_scsih_ublock_io_device(ioc, wwid);

	return;
}