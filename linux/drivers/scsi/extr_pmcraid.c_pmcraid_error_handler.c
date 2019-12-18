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
typedef  int u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; TYPE_2__* device; int /*<<< orphan*/ * cmnd; } ;
struct pmcraid_resource_entry {int sync_reqd; int /*<<< orphan*/  cfg_entry; int /*<<< orphan*/  reset_progress; int /*<<< orphan*/  write_failures; int /*<<< orphan*/  read_failures; } ;
struct pmcraid_ioasa {int /*<<< orphan*/  sense_data; int /*<<< orphan*/  auto_sense_length; int /*<<< orphan*/  ioasc; } ;
struct pmcraid_instance {int /*<<< orphan*/  host; } ;
struct pmcraid_cmd {TYPE_1__* ioa_cb; struct pmcraid_instance* drv_inst; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; struct pmcraid_resource_entry* hostdata; } ;
struct TYPE_3__ {struct pmcraid_ioasa ioasa; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_IMM_RETRY ; 
 int DID_NO_CONNECT ; 
 int DID_PASSTHROUGH ; 
#define  PMCRAID_IOASC_AC_TERMINATED_BY_HOST 136 
#define  PMCRAID_IOASC_HW_CANNOT_COMMUNICATE 135 
#define  PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR 134 
#define  PMCRAID_IOASC_IR_INVALID_RESOURCE_HANDLE 133 
#define  PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC 132 
#define  PMCRAID_IOASC_NR_INIT_CMD_REQUIRED 131 
#define  PMCRAID_IOASC_NR_SYNC_REQUIRED 130 
 int /*<<< orphan*/  PMCRAID_IOASC_SENSE_KEY (int) ; 
 int PMCRAID_IOASC_SENSE_MASK ; 
 int PMCRAID_IOASC_SENSE_STATUS (int) ; 
#define  PMCRAID_IOASC_UA_BUS_WAS_RESET 129 
#define  PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER 128 
 int /*<<< orphan*/  RECOVERED_ERROR ; 
 scalar_t__ RES_IS_GSCSI (int /*<<< orphan*/ ) ; 
 int SAM_STAT_ACA_ACTIVE ; 
 int SAM_STAT_CHECK_CONDITION ; 
 scalar_t__ SCSI_CMD_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCSI_READ_CMD ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ SCSI_WRITE_CMD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min_t (int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_cancel_all (struct pmcraid_cmd*,int) ; 
 int /*<<< orphan*/  pmcraid_erp_done (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_frame_auto_sense (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_info (char*) ; 
 int /*<<< orphan*/  pmcraid_ioasc_logger (int,struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_request_sense (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  scsi_report_bus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int pmcraid_error_handler(struct pmcraid_cmd *cmd)
{
	struct scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	struct pmcraid_resource_entry *res = scsi_cmd->device->hostdata;
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	struct pmcraid_ioasa *ioasa = &cmd->ioa_cb->ioasa;
	u32 ioasc = le32_to_cpu(ioasa->ioasc);
	u32 masked_ioasc = ioasc & PMCRAID_IOASC_SENSE_MASK;
	bool sense_copied = false;

	if (!res) {
		pmcraid_info("resource pointer is NULL\n");
		return 0;
	}

	/* If this was a SCSI read/write command keep count of errors */
	if (SCSI_CMD_TYPE(scsi_cmd->cmnd[0]) == SCSI_READ_CMD)
		atomic_inc(&res->read_failures);
	else if (SCSI_CMD_TYPE(scsi_cmd->cmnd[0]) == SCSI_WRITE_CMD)
		atomic_inc(&res->write_failures);

	if (!RES_IS_GSCSI(res->cfg_entry) &&
		masked_ioasc != PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR) {
		pmcraid_frame_auto_sense(cmd);
	}

	/* Log IOASC/IOASA information based on user settings */
	pmcraid_ioasc_logger(ioasc, cmd);

	switch (masked_ioasc) {

	case PMCRAID_IOASC_AC_TERMINATED_BY_HOST:
		scsi_cmd->result |= (DID_ABORT << 16);
		break;

	case PMCRAID_IOASC_IR_INVALID_RESOURCE_HANDLE:
	case PMCRAID_IOASC_HW_CANNOT_COMMUNICATE:
		scsi_cmd->result |= (DID_NO_CONNECT << 16);
		break;

	case PMCRAID_IOASC_NR_SYNC_REQUIRED:
		res->sync_reqd = 1;
		scsi_cmd->result |= (DID_IMM_RETRY << 16);
		break;

	case PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC:
		scsi_cmd->result |= (DID_PASSTHROUGH << 16);
		break;

	case PMCRAID_IOASC_UA_BUS_WAS_RESET:
	case PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER:
		if (!res->reset_progress)
			scsi_report_bus_reset(pinstance->host,
					      scsi_cmd->device->channel);
		scsi_cmd->result |= (DID_ERROR << 16);
		break;

	case PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR:
		scsi_cmd->result |= PMCRAID_IOASC_SENSE_STATUS(ioasc);
		res->sync_reqd = 1;

		/* if check_condition is not active return with error otherwise
		 * get/frame the sense buffer
		 */
		if (PMCRAID_IOASC_SENSE_STATUS(ioasc) !=
		    SAM_STAT_CHECK_CONDITION &&
		    PMCRAID_IOASC_SENSE_STATUS(ioasc) != SAM_STAT_ACA_ACTIVE)
			return 0;

		/* If we have auto sense data as part of IOASA pass it to
		 * mid-layer
		 */
		if (ioasa->auto_sense_length != 0) {
			short sense_len = le16_to_cpu(ioasa->auto_sense_length);
			int data_size = min_t(u16, sense_len,
					      SCSI_SENSE_BUFFERSIZE);

			memcpy(scsi_cmd->sense_buffer,
			       ioasa->sense_data,
			       data_size);
			sense_copied = true;
		}

		if (RES_IS_GSCSI(res->cfg_entry))
			pmcraid_cancel_all(cmd, sense_copied);
		else if (sense_copied)
			pmcraid_erp_done(cmd);
		else
			pmcraid_request_sense(cmd);

		return 1;

	case PMCRAID_IOASC_NR_INIT_CMD_REQUIRED:
		break;

	default:
		if (PMCRAID_IOASC_SENSE_KEY(ioasc) > RECOVERED_ERROR)
			scsi_cmd->result |= (DID_ERROR << 16);
		break;
	}
	return 0;
}