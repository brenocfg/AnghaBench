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
struct scsi_cmnd {char* sense_buffer; int* cmnd; int result; int underflow; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct fib {int flags; } ;
struct aac_srb_reply {void* scsi_status; int /*<<< orphan*/  sense_data; void* status; void* sense_data_size; void* srb_status; void* data_xfer_length; } ;

/* Variables and functions */
 int ABORT ; 
 int ATA_12 ; 
 int ATA_16 ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int COMMAND_COMPLETE ; 
 int DID_ABORT ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_PARITY ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
 int FIB_CONTEXT_FLAG_FASTRESP ; 
#define  INQUIRY 167 
 int MESSAGE_REJECT ; 
 int MSG_PARITY_ERROR ; 
#define  READ_10 166 
#define  READ_12 165 
#define  READ_16 164 
#define  READ_6 163 
 int SAM_STAT_CHECK_CONDITION ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
#define  SRB_STATUS_ABORTED 162 
#define  SRB_STATUS_ABORT_FAILED 161 
#define  SRB_STATUS_BAD_FUNCTION 160 
#define  SRB_STATUS_BAD_SRB_BLOCK_LENGTH 159 
#define  SRB_STATUS_BUSY 158 
#define  SRB_STATUS_BUS_RESET 157 
#define  SRB_STATUS_COMMAND_TIMEOUT 156 
#define  SRB_STATUS_DATA_OVERRUN 155 
#define  SRB_STATUS_DELAYED_RETRY 154 
#define  SRB_STATUS_DOMAIN_VALIDATION_FAIL 153 
#define  SRB_STATUS_ERROR 152 
#define  SRB_STATUS_ERROR_RECOVERY 151 
#define  SRB_STATUS_FORCE_ABORT 150 
#define  SRB_STATUS_INVALID_LUN 149 
#define  SRB_STATUS_INVALID_PATH_ID 148 
#define  SRB_STATUS_INVALID_REQUEST 147 
#define  SRB_STATUS_INVALID_TARGET_ID 146 
#define  SRB_STATUS_MESSAGE_REJECTED 145 
#define  SRB_STATUS_NOT_IN_USE 144 
#define  SRB_STATUS_NOT_STARTED 143 
#define  SRB_STATUS_NO_DEVICE 142 
#define  SRB_STATUS_NO_HBA 141 
#define  SRB_STATUS_PARITY_ERROR 140 
#define  SRB_STATUS_PENDING 139 
#define  SRB_STATUS_PHASE_SEQUENCE_FAILURE 138 
#define  SRB_STATUS_REQUEST_FLUSHED 137 
#define  SRB_STATUS_REQUEST_SENSE_FAILED 136 
#define  SRB_STATUS_SELECTION_TIMEOUT 135 
#define  SRB_STATUS_SUCCESS 134 
#define  SRB_STATUS_TIMEOUT 133 
#define  SRB_STATUS_UNEXPECTED_BUS_FREE 132 
 int ST_OK ; 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int /*<<< orphan*/  aac_expose_phy_device (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_get_status_string (int) ; 
 int /*<<< orphan*/  aac_valid_context (struct scsi_cmnd*,struct fib*) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ expose_physicals ; 
 scalar_t__ fib_data (struct fib*) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void aac_srb_callback(void *context, struct fib * fibptr)
{
	struct aac_srb_reply *srbreply;
	struct scsi_cmnd *scsicmd;

	scsicmd = (struct scsi_cmnd *) context;

	if (!aac_valid_context(scsicmd, fibptr))
		return;

	BUG_ON(fibptr == NULL);

	srbreply = (struct aac_srb_reply *) fib_data(fibptr);

	scsicmd->sense_buffer[0] = '\0';  /* Initialize sense valid flag to false */

	if (fibptr->flags & FIB_CONTEXT_FLAG_FASTRESP) {
		/* fast response */
		srbreply->srb_status = cpu_to_le32(SRB_STATUS_SUCCESS);
		srbreply->scsi_status = cpu_to_le32(SAM_STAT_GOOD);
	} else {
		/*
		 *	Calculate resid for sg
		 */
		scsi_set_resid(scsicmd, scsi_bufflen(scsicmd)
				   - le32_to_cpu(srbreply->data_xfer_length));
	}


	scsi_dma_unmap(scsicmd);

	/* expose physical device if expose_physicald flag is on */
	if (scsicmd->cmnd[0] == INQUIRY && !(scsicmd->cmnd[1] & 0x01)
	  && expose_physicals > 0)
		aac_expose_phy_device(scsicmd);

	/*
	 * First check the fib status
	 */

	if (le32_to_cpu(srbreply->status) != ST_OK) {
		int len;

		pr_warn("aac_srb_callback: srb failed, status = %d\n",
				le32_to_cpu(srbreply->status));
		len = min_t(u32, le32_to_cpu(srbreply->sense_data_size),
			    SCSI_SENSE_BUFFERSIZE);
		scsicmd->result = DID_ERROR << 16
				| COMMAND_COMPLETE << 8
				| SAM_STAT_CHECK_CONDITION;
		memcpy(scsicmd->sense_buffer,
				srbreply->sense_data, len);
	}

	/*
	 * Next check the srb status
	 */
	switch ((le32_to_cpu(srbreply->srb_status))&0x3f) {
	case SRB_STATUS_ERROR_RECOVERY:
	case SRB_STATUS_PENDING:
	case SRB_STATUS_SUCCESS:
		scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8;
		break;
	case SRB_STATUS_DATA_OVERRUN:
		switch (scsicmd->cmnd[0]) {
		case  READ_6:
		case  WRITE_6:
		case  READ_10:
		case  WRITE_10:
		case  READ_12:
		case  WRITE_12:
		case  READ_16:
		case  WRITE_16:
			if (le32_to_cpu(srbreply->data_xfer_length)
						< scsicmd->underflow)
				pr_warn("aacraid: SCSI CMD underflow\n");
			else
				pr_warn("aacraid: SCSI CMD Data Overrun\n");
			scsicmd->result = DID_ERROR << 16
					| COMMAND_COMPLETE << 8;
			break;
		case INQUIRY:
			scsicmd->result = DID_OK << 16
					| COMMAND_COMPLETE << 8;
			break;
		default:
			scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8;
			break;
		}
		break;
	case SRB_STATUS_ABORTED:
		scsicmd->result = DID_ABORT << 16 | ABORT << 8;
		break;
	case SRB_STATUS_ABORT_FAILED:
		/*
		 * Not sure about this one - but assuming the
		 * hba was trying to abort for some reason
		 */
		scsicmd->result = DID_ERROR << 16 | ABORT << 8;
		break;
	case SRB_STATUS_PARITY_ERROR:
		scsicmd->result = DID_PARITY << 16
				| MSG_PARITY_ERROR << 8;
		break;
	case SRB_STATUS_NO_DEVICE:
	case SRB_STATUS_INVALID_PATH_ID:
	case SRB_STATUS_INVALID_TARGET_ID:
	case SRB_STATUS_INVALID_LUN:
	case SRB_STATUS_SELECTION_TIMEOUT:
		scsicmd->result = DID_NO_CONNECT << 16
				| COMMAND_COMPLETE << 8;
		break;

	case SRB_STATUS_COMMAND_TIMEOUT:
	case SRB_STATUS_TIMEOUT:
		scsicmd->result = DID_TIME_OUT << 16
				| COMMAND_COMPLETE << 8;
		break;

	case SRB_STATUS_BUSY:
		scsicmd->result = DID_BUS_BUSY << 16
				| COMMAND_COMPLETE << 8;
		break;

	case SRB_STATUS_BUS_RESET:
		scsicmd->result = DID_RESET << 16
				| COMMAND_COMPLETE << 8;
		break;

	case SRB_STATUS_MESSAGE_REJECTED:
		scsicmd->result = DID_ERROR << 16
				| MESSAGE_REJECT << 8;
		break;
	case SRB_STATUS_REQUEST_FLUSHED:
	case SRB_STATUS_ERROR:
	case SRB_STATUS_INVALID_REQUEST:
	case SRB_STATUS_REQUEST_SENSE_FAILED:
	case SRB_STATUS_NO_HBA:
	case SRB_STATUS_UNEXPECTED_BUS_FREE:
	case SRB_STATUS_PHASE_SEQUENCE_FAILURE:
	case SRB_STATUS_BAD_SRB_BLOCK_LENGTH:
	case SRB_STATUS_DELAYED_RETRY:
	case SRB_STATUS_BAD_FUNCTION:
	case SRB_STATUS_NOT_STARTED:
	case SRB_STATUS_NOT_IN_USE:
	case SRB_STATUS_FORCE_ABORT:
	case SRB_STATUS_DOMAIN_VALIDATION_FAIL:
	default:
#ifdef AAC_DETAILED_STATUS_INFO
		pr_info("aacraid: SRB ERROR(%u) %s scsi cmd 0x%x -scsi status 0x%x\n",
			le32_to_cpu(srbreply->srb_status) & 0x3F,
			aac_get_status_string(
				le32_to_cpu(srbreply->srb_status) & 0x3F),
			scsicmd->cmnd[0],
			le32_to_cpu(srbreply->scsi_status));
#endif
		/*
		 * When the CC bit is SET by the host in ATA pass thru CDB,
		 *  driver is supposed to return DID_OK
		 *
		 * When the CC bit is RESET by the host, driver should
		 *  return DID_ERROR
		 */
		if ((scsicmd->cmnd[0] == ATA_12)
			|| (scsicmd->cmnd[0] == ATA_16)) {

			if (scsicmd->cmnd[2] & (0x01 << 5)) {
				scsicmd->result = DID_OK << 16
					| COMMAND_COMPLETE << 8;
			break;
			} else {
				scsicmd->result = DID_ERROR << 16
					| COMMAND_COMPLETE << 8;
			break;
			}
		} else {
			scsicmd->result = DID_ERROR << 16
				| COMMAND_COMPLETE << 8;
			break;
		}
	}
	if (le32_to_cpu(srbreply->scsi_status)
			== SAM_STAT_CHECK_CONDITION) {
		int len;

		scsicmd->result |= SAM_STAT_CHECK_CONDITION;
		len = min_t(u32, le32_to_cpu(srbreply->sense_data_size),
			    SCSI_SENSE_BUFFERSIZE);
#ifdef AAC_DETAILED_STATUS_INFO
		pr_warn("aac_srb_callback: check condition, status = %d len=%d\n",
					le32_to_cpu(srbreply->status), len);
#endif
		memcpy(scsicmd->sense_buffer,
				srbreply->sense_data, len);
	}

	/*
	 * OR in the scsi status (already shifted up a bit)
	 */
	scsicmd->result |= le32_to_cpu(srbreply->scsi_status);

	aac_fib_complete(fibptr);
	scsicmd->scsi_done(scsicmd);
}