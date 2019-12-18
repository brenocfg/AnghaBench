#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct _sas_device {int /*<<< orphan*/  slot; scalar_t__ enclosure_logical_id; int /*<<< orphan*/  phy; scalar_t__ sas_address; } ;
struct _pcie_device {scalar_t__ enclosure_handle; int /*<<< orphan*/  slot; scalar_t__ enclosure_logical_id; int /*<<< orphan*/  port_num; scalar_t__ wwid; } ;
struct MPT3SAS_ADAPTER {int logging_level; char* tmp_string; } ;
struct TYPE_14__ {scalar_t__ IOCLogInfo; scalar_t__ IOCStatus; } ;
struct TYPE_9__ {int PageType; int PageNumber; } ;
struct TYPE_13__ {int Function; int ExtPageType; TYPE_1__ Header; } ;
struct TYPE_12__ {int SCSIState; int /*<<< orphan*/  SCSIStatus; scalar_t__ DevHandle; } ;
struct TYPE_10__ {int* CDB32; } ;
struct TYPE_11__ {scalar_t__ IoFlags; TYPE_2__ CDB; } ;
typedef  TYPE_3__ Mpi2SCSIIORequest_t ;
typedef  TYPE_4__ Mpi2SCSIIOReply_t ;
typedef  TYPE_5__ Mpi2ConfigRequest_t ;
typedef  TYPE_6__ MPI2DefaultReply_t ;

/* Variables and functions */
 int MPI2_CONFIG_PAGETYPE_MASK ; 
#define  MPI2_FUNCTION_CONFIG 144 
#define  MPI2_FUNCTION_DIAG_BUFFER_POST 143 
#define  MPI2_FUNCTION_DIAG_RELEASE 142 
#define  MPI2_FUNCTION_EVENT_NOTIFICATION 141 
#define  MPI2_FUNCTION_FW_DOWNLOAD 140 
#define  MPI2_FUNCTION_FW_UPLOAD 139 
#define  MPI2_FUNCTION_IOC_FACTS 138 
#define  MPI2_FUNCTION_IOC_INIT 137 
#define  MPI2_FUNCTION_PORT_ENABLE 136 
#define  MPI2_FUNCTION_PORT_FACTS 135 
#define  MPI2_FUNCTION_RAID_ACTION 134 
#define  MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH 133 
#define  MPI2_FUNCTION_SAS_IO_UNIT_CONTROL 132 
#define  MPI2_FUNCTION_SATA_PASSTHROUGH 131 
#define  MPI2_FUNCTION_SCSI_IO_REQUEST 130 
#define  MPI2_FUNCTION_SCSI_TASK_MGMT 129 
#define  MPI2_FUNCTION_SMP_PASSTHROUGH 128 
 int MPT_DEBUG_IOCTL ; 
 int /*<<< orphan*/  MPT_STRING_LENGTH ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int /*<<< orphan*/  ioc_warn (struct MPT3SAS_ADAPTER*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 TYPE_5__* mpt3sas_base_get_msg_frame (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 struct _pcie_device* mpt3sas_get_pdev_by_handle (struct MPT3SAS_ADAPTER*,int) ; 
 struct _sas_device* mpt3sas_get_sdev_by_handle (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,...) ; 

__attribute__((used)) static void
_ctl_display_some_debug(struct MPT3SAS_ADAPTER *ioc, u16 smid,
	char *calling_function_name, MPI2DefaultReply_t *mpi_reply)
{
	Mpi2ConfigRequest_t *mpi_request;
	char *desc = NULL;

	if (!(ioc->logging_level & MPT_DEBUG_IOCTL))
		return;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	switch (mpi_request->Function) {
	case MPI2_FUNCTION_SCSI_IO_REQUEST:
	{
		Mpi2SCSIIORequest_t *scsi_request =
		    (Mpi2SCSIIORequest_t *)mpi_request;

		snprintf(ioc->tmp_string, MPT_STRING_LENGTH,
		    "scsi_io, cmd(0x%02x), cdb_len(%d)",
		    scsi_request->CDB.CDB32[0],
		    le16_to_cpu(scsi_request->IoFlags) & 0xF);
		desc = ioc->tmp_string;
		break;
	}
	case MPI2_FUNCTION_SCSI_TASK_MGMT:
		desc = "task_mgmt";
		break;
	case MPI2_FUNCTION_IOC_INIT:
		desc = "ioc_init";
		break;
	case MPI2_FUNCTION_IOC_FACTS:
		desc = "ioc_facts";
		break;
	case MPI2_FUNCTION_CONFIG:
	{
		Mpi2ConfigRequest_t *config_request =
		    (Mpi2ConfigRequest_t *)mpi_request;

		snprintf(ioc->tmp_string, MPT_STRING_LENGTH,
		    "config, type(0x%02x), ext_type(0x%02x), number(%d)",
		    (config_request->Header.PageType &
		     MPI2_CONFIG_PAGETYPE_MASK), config_request->ExtPageType,
		    config_request->Header.PageNumber);
		desc = ioc->tmp_string;
		break;
	}
	case MPI2_FUNCTION_PORT_FACTS:
		desc = "port_facts";
		break;
	case MPI2_FUNCTION_PORT_ENABLE:
		desc = "port_enable";
		break;
	case MPI2_FUNCTION_EVENT_NOTIFICATION:
		desc = "event_notification";
		break;
	case MPI2_FUNCTION_FW_DOWNLOAD:
		desc = "fw_download";
		break;
	case MPI2_FUNCTION_FW_UPLOAD:
		desc = "fw_upload";
		break;
	case MPI2_FUNCTION_RAID_ACTION:
		desc = "raid_action";
		break;
	case MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
	{
		Mpi2SCSIIORequest_t *scsi_request =
		    (Mpi2SCSIIORequest_t *)mpi_request;

		snprintf(ioc->tmp_string, MPT_STRING_LENGTH,
		    "raid_pass, cmd(0x%02x), cdb_len(%d)",
		    scsi_request->CDB.CDB32[0],
		    le16_to_cpu(scsi_request->IoFlags) & 0xF);
		desc = ioc->tmp_string;
		break;
	}
	case MPI2_FUNCTION_SAS_IO_UNIT_CONTROL:
		desc = "sas_iounit_cntl";
		break;
	case MPI2_FUNCTION_SATA_PASSTHROUGH:
		desc = "sata_pass";
		break;
	case MPI2_FUNCTION_DIAG_BUFFER_POST:
		desc = "diag_buffer_post";
		break;
	case MPI2_FUNCTION_DIAG_RELEASE:
		desc = "diag_release";
		break;
	case MPI2_FUNCTION_SMP_PASSTHROUGH:
		desc = "smp_passthrough";
		break;
	}

	if (!desc)
		return;

	ioc_info(ioc, "%s: %s, smid(%d)\n", calling_function_name, desc, smid);

	if (!mpi_reply)
		return;

	if (mpi_reply->IOCStatus || mpi_reply->IOCLogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), loginfo(0x%08x)\n",
			 le16_to_cpu(mpi_reply->IOCStatus),
			 le32_to_cpu(mpi_reply->IOCLogInfo));

	if (mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
	    mpi_request->Function ==
	    MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH) {
		Mpi2SCSIIOReply_t *scsi_reply =
		    (Mpi2SCSIIOReply_t *)mpi_reply;
		struct _sas_device *sas_device = NULL;
		struct _pcie_device *pcie_device = NULL;

		sas_device = mpt3sas_get_sdev_by_handle(ioc,
		    le16_to_cpu(scsi_reply->DevHandle));
		if (sas_device) {
			ioc_warn(ioc, "\tsas_address(0x%016llx), phy(%d)\n",
				 (u64)sas_device->sas_address,
				 sas_device->phy);
			ioc_warn(ioc, "\tenclosure_logical_id(0x%016llx), slot(%d)\n",
				 (u64)sas_device->enclosure_logical_id,
				 sas_device->slot);
			sas_device_put(sas_device);
		}
		if (!sas_device) {
			pcie_device = mpt3sas_get_pdev_by_handle(ioc,
				le16_to_cpu(scsi_reply->DevHandle));
			if (pcie_device) {
				ioc_warn(ioc, "\tWWID(0x%016llx), port(%d)\n",
					 (unsigned long long)pcie_device->wwid,
					 pcie_device->port_num);
				if (pcie_device->enclosure_handle != 0)
					ioc_warn(ioc, "\tenclosure_logical_id(0x%016llx), slot(%d)\n",
						 (u64)pcie_device->enclosure_logical_id,
						 pcie_device->slot);
				pcie_device_put(pcie_device);
			}
		}
		if (scsi_reply->SCSIState || scsi_reply->SCSIStatus)
			ioc_info(ioc, "\tscsi_state(0x%02x), scsi_status(0x%02x)\n",
				 scsi_reply->SCSIState,
				 scsi_reply->SCSIStatus);
	}
}