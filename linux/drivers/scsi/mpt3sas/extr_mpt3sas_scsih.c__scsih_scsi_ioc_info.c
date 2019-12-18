#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sense_info {char* skey; int asc; char* ascq; } ;
struct scsi_target {struct MPT3SAS_TARGET* hostdata; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  result; int /*<<< orphan*/  underflow; TYPE_1__* device; } ;
struct _sas_device {int /*<<< orphan*/  phy; scalar_t__ sas_address; } ;
struct _pcie_device {scalar_t__ enclosure_handle; scalar_t__* connector_name; int /*<<< orphan*/  enclosure_level; scalar_t__* slot; scalar_t__ enclosure_logical_id; scalar_t__* port_num; scalar_t__ wwid; } ;
struct MPT3SAS_TARGET {int flags; scalar_t__ sas_address; } ;
struct MPT3SAS_ADAPTER {char* tmp_string; scalar_t__ hide_ir_msg; } ;
struct TYPE_5__ {int SCSIState; int SCSIStatus; int /*<<< orphan*/  ResponseInfo; int /*<<< orphan*/  SenseCount; int /*<<< orphan*/  TransferCount; int /*<<< orphan*/  TaskTag; int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  IOCLogInfo; int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_4__ {struct scsi_target* sdev_target; } ;
typedef  TYPE_2__ Mpi2SCSIIOReply_t ;

/* Variables and functions */
#define  MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR 156 
#define  MPI2_IOCSTATUS_EEDP_GUARD_ERROR 155 
#define  MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR 154 
#define  MPI2_IOCSTATUS_INSUFFICIENT_POWER 153 
#define  MPI2_IOCSTATUS_INVALID_FUNCTION 152 
 int MPI2_IOCSTATUS_MASK ; 
#define  MPI2_IOCSTATUS_SCSI_DATA_OVERRUN 151 
#define  MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN 150 
#define  MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE 149 
#define  MPI2_IOCSTATUS_SCSI_EXT_TERMINATED 148 
#define  MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE 147 
#define  MPI2_IOCSTATUS_SCSI_IOC_TERMINATED 146 
#define  MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR 145 
#define  MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR 144 
#define  MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR 143 
#define  MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH 142 
#define  MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED 141 
#define  MPI2_IOCSTATUS_SCSI_TASK_TERMINATED 140 
#define  MPI2_IOCSTATUS_SUCCESS 139 
 int MPI2_SCSI_STATE_AUTOSENSE_FAILED ; 
 int MPI2_SCSI_STATE_AUTOSENSE_VALID ; 
 int MPI2_SCSI_STATE_NO_SCSI_STATUS ; 
 int MPI2_SCSI_STATE_RESPONSE_INFO_VALID ; 
 int MPI2_SCSI_STATE_TERMINATED ; 
#define  MPI2_SCSI_STATUS_ACA_ACTIVE 138 
#define  MPI2_SCSI_STATUS_BUSY 137 
#define  MPI2_SCSI_STATUS_CHECK_CONDITION 136 
#define  MPI2_SCSI_STATUS_COMMAND_TERMINATED 135 
#define  MPI2_SCSI_STATUS_CONDITION_MET 134 
#define  MPI2_SCSI_STATUS_GOOD 133 
#define  MPI2_SCSI_STATUS_INTERMEDIATE 132 
#define  MPI2_SCSI_STATUS_INTERMEDIATE_CONDMET 131 
#define  MPI2_SCSI_STATUS_RESERVATION_CONFLICT 130 
#define  MPI2_SCSI_STATUS_TASK_ABORTED 129 
#define  MPI2_SCSI_STATUS_TASK_SET_FULL 128 
 int MPT_TARGET_FLAGS_PCIE_DEVICE ; 
 int MPT_TARGET_FLAGS_VOLUME ; 
 int /*<<< orphan*/  _scsih_display_enclosure_chassis_info (struct MPT3SAS_ADAPTER*,struct _sas_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _scsih_normalize_sense (int /*<<< orphan*/ ,struct sense_info*) ; 
 int /*<<< orphan*/  _scsih_response_code (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ioc_warn (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct _pcie_device* mpt3sas_get_pdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 struct _sas_device* mpt3sas_get_sdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void
_scsih_scsi_ioc_info(struct MPT3SAS_ADAPTER *ioc, struct scsi_cmnd *scmd,
	Mpi2SCSIIOReply_t *mpi_reply, u16 smid)
{
	u32 response_info;
	u8 *response_bytes;
	u16 ioc_status = le16_to_cpu(mpi_reply->IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	u8 scsi_state = mpi_reply->SCSIState;
	u8 scsi_status = mpi_reply->SCSIStatus;
	char *desc_ioc_state = NULL;
	char *desc_scsi_status = NULL;
	char *desc_scsi_state = ioc->tmp_string;
	u32 log_info = le32_to_cpu(mpi_reply->IOCLogInfo);
	struct _sas_device *sas_device = NULL;
	struct _pcie_device *pcie_device = NULL;
	struct scsi_target *starget = scmd->device->sdev_target;
	struct MPT3SAS_TARGET *priv_target = starget->hostdata;
	char *device_str = NULL;

	if (!priv_target)
		return;
	if (ioc->hide_ir_msg)
		device_str = "WarpDrive";
	else
		device_str = "volume";

	if (log_info == 0x31170000)
		return;

	switch (ioc_status) {
	case MPI2_IOCSTATUS_SUCCESS:
		desc_ioc_state = "success";
		break;
	case MPI2_IOCSTATUS_INVALID_FUNCTION:
		desc_ioc_state = "invalid function";
		break;
	case MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR:
		desc_ioc_state = "scsi recovered error";
		break;
	case MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE:
		desc_ioc_state = "scsi invalid dev handle";
		break;
	case MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		desc_ioc_state = "scsi device not there";
		break;
	case MPI2_IOCSTATUS_SCSI_DATA_OVERRUN:
		desc_ioc_state = "scsi data overrun";
		break;
	case MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN:
		desc_ioc_state = "scsi data underrun";
		break;
	case MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR:
		desc_ioc_state = "scsi io data error";
		break;
	case MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR:
		desc_ioc_state = "scsi protocol error";
		break;
	case MPI2_IOCSTATUS_SCSI_TASK_TERMINATED:
		desc_ioc_state = "scsi task terminated";
		break;
	case MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
		desc_ioc_state = "scsi residual mismatch";
		break;
	case MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
		desc_ioc_state = "scsi task mgmt failed";
		break;
	case MPI2_IOCSTATUS_SCSI_IOC_TERMINATED:
		desc_ioc_state = "scsi ioc terminated";
		break;
	case MPI2_IOCSTATUS_SCSI_EXT_TERMINATED:
		desc_ioc_state = "scsi ext terminated";
		break;
	case MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
		desc_ioc_state = "eedp guard error";
		break;
	case MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
		desc_ioc_state = "eedp ref tag error";
		break;
	case MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		desc_ioc_state = "eedp app tag error";
		break;
	case MPI2_IOCSTATUS_INSUFFICIENT_POWER:
		desc_ioc_state = "insufficient power";
		break;
	default:
		desc_ioc_state = "unknown";
		break;
	}

	switch (scsi_status) {
	case MPI2_SCSI_STATUS_GOOD:
		desc_scsi_status = "good";
		break;
	case MPI2_SCSI_STATUS_CHECK_CONDITION:
		desc_scsi_status = "check condition";
		break;
	case MPI2_SCSI_STATUS_CONDITION_MET:
		desc_scsi_status = "condition met";
		break;
	case MPI2_SCSI_STATUS_BUSY:
		desc_scsi_status = "busy";
		break;
	case MPI2_SCSI_STATUS_INTERMEDIATE:
		desc_scsi_status = "intermediate";
		break;
	case MPI2_SCSI_STATUS_INTERMEDIATE_CONDMET:
		desc_scsi_status = "intermediate condmet";
		break;
	case MPI2_SCSI_STATUS_RESERVATION_CONFLICT:
		desc_scsi_status = "reservation conflict";
		break;
	case MPI2_SCSI_STATUS_COMMAND_TERMINATED:
		desc_scsi_status = "command terminated";
		break;
	case MPI2_SCSI_STATUS_TASK_SET_FULL:
		desc_scsi_status = "task set full";
		break;
	case MPI2_SCSI_STATUS_ACA_ACTIVE:
		desc_scsi_status = "aca active";
		break;
	case MPI2_SCSI_STATUS_TASK_ABORTED:
		desc_scsi_status = "task aborted";
		break;
	default:
		desc_scsi_status = "unknown";
		break;
	}

	desc_scsi_state[0] = '\0';
	if (!scsi_state)
		desc_scsi_state = " ";
	if (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID)
		strcat(desc_scsi_state, "response info ");
	if (scsi_state & MPI2_SCSI_STATE_TERMINATED)
		strcat(desc_scsi_state, "state terminated ");
	if (scsi_state & MPI2_SCSI_STATE_NO_SCSI_STATUS)
		strcat(desc_scsi_state, "no status ");
	if (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_FAILED)
		strcat(desc_scsi_state, "autosense failed ");
	if (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID)
		strcat(desc_scsi_state, "autosense valid ");

	scsi_print_command(scmd);

	if (priv_target->flags & MPT_TARGET_FLAGS_VOLUME) {
		ioc_warn(ioc, "\t%s wwid(0x%016llx)\n",
			 device_str, (u64)priv_target->sas_address);
	} else if (priv_target->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) {
		pcie_device = mpt3sas_get_pdev_from_target(ioc, priv_target);
		if (pcie_device) {
			ioc_info(ioc, "\twwid(0x%016llx), port(%d)\n",
				 (u64)pcie_device->wwid, pcie_device->port_num);
			if (pcie_device->enclosure_handle != 0)
				ioc_info(ioc, "\tenclosure logical id(0x%016llx), slot(%d)\n",
					 (u64)pcie_device->enclosure_logical_id,
					 pcie_device->slot);
			if (pcie_device->connector_name[0])
				ioc_info(ioc, "\tenclosure level(0x%04x), connector name( %s)\n",
					 pcie_device->enclosure_level,
					 pcie_device->connector_name);
			pcie_device_put(pcie_device);
		}
	} else {
		sas_device = mpt3sas_get_sdev_from_target(ioc, priv_target);
		if (sas_device) {
			ioc_warn(ioc, "\tsas_address(0x%016llx), phy(%d)\n",
				 (u64)sas_device->sas_address, sas_device->phy);

			_scsih_display_enclosure_chassis_info(ioc, sas_device,
			    NULL, NULL);

			sas_device_put(sas_device);
		}
	}

	ioc_warn(ioc, "\thandle(0x%04x), ioc_status(%s)(0x%04x), smid(%d)\n",
		 le16_to_cpu(mpi_reply->DevHandle),
		 desc_ioc_state, ioc_status, smid);
	ioc_warn(ioc, "\trequest_len(%d), underflow(%d), resid(%d)\n",
		 scsi_bufflen(scmd), scmd->underflow, scsi_get_resid(scmd));
	ioc_warn(ioc, "\ttag(%d), transfer_count(%d), sc->result(0x%08x)\n",
		 le16_to_cpu(mpi_reply->TaskTag),
		 le32_to_cpu(mpi_reply->TransferCount), scmd->result);
	ioc_warn(ioc, "\tscsi_status(%s)(0x%02x), scsi_state(%s)(0x%02x)\n",
		 desc_scsi_status, scsi_status, desc_scsi_state, scsi_state);

	if (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID) {
		struct sense_info data;
		_scsih_normalize_sense(scmd->sense_buffer, &data);
		ioc_warn(ioc, "\t[sense_key,asc,ascq]: [0x%02x,0x%02x,0x%02x], count(%d)\n",
			 data.skey, data.asc, data.ascq,
			 le32_to_cpu(mpi_reply->SenseCount));
	}
	if (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID) {
		response_info = le32_to_cpu(mpi_reply->ResponseInfo);
		response_bytes = (u8 *)&response_info;
		_scsih_response_code(ioc, response_bytes[0]);
	}
}