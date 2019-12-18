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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
#define  CAM_AUTOSENSE_FAIL 152 
#define  CAM_BDR_SENT 151 
#define  CAM_BUSY 150 
#define  CAM_CCB_LEN_ERR 149 
#define  CAM_CMD_TIMEOUT 148 
#define  CAM_DATA_RUN_ERR 147 
#define  CAM_NO_HBA 146 
#define  CAM_PATH_INVALID 145 
#define  CAM_PROVIDE_FAIL 144 
#define  CAM_REQUEUE_REQ 143 
#define  CAM_REQ_ABORTED 142 
#define  CAM_REQ_CMP 141 
#define  CAM_REQ_CMP_ERR 140 
#define  CAM_REQ_INPROG 139 
#define  CAM_REQ_INVALID 138 
#define  CAM_REQ_TERMIO 137 
#define  CAM_REQ_TOO_BIG 136 
#define  CAM_SCSI_BUS_RESET 135 
#define  CAM_SCSI_STATUS_ERROR 134 
#define  CAM_SEL_TIMEOUT 133 
#define  CAM_SEQUENCE_FAIL 132 
#define  CAM_UA_ABORT 131 
#define  CAM_UNCOR_PARITY 130 
#define  CAM_UNEXP_BUSFREE 129 
#define  CAM_UNREC_HBA_ERROR 128 
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  DID_BAD_TARGET ; 
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  DID_PARITY ; 
 int /*<<< orphan*/  DID_REQUEUE ; 
 int /*<<< orphan*/  DID_RESET ; 
 int /*<<< orphan*/  DID_TIME_OUT ; 
 int ahc_cmd_get_transaction_status (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ahc_cmd_set_transaction_status (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void
ahc_linux_queue_cmd_complete(struct ahc_softc *ahc, struct scsi_cmnd *cmd)
{
	/*
	 * Map CAM error codes into Linux Error codes.  We
	 * avoid the conversion so that the DV code has the
	 * full error information available when making
	 * state change decisions.
	 */
	{
		u_int new_status;

		switch (ahc_cmd_get_transaction_status(cmd)) {
		case CAM_REQ_INPROG:
		case CAM_REQ_CMP:
		case CAM_SCSI_STATUS_ERROR:
			new_status = DID_OK;
			break;
		case CAM_REQ_ABORTED:
			new_status = DID_ABORT;
			break;
		case CAM_BUSY:
			new_status = DID_BUS_BUSY;
			break;
		case CAM_REQ_INVALID:
		case CAM_PATH_INVALID:
			new_status = DID_BAD_TARGET;
			break;
		case CAM_SEL_TIMEOUT:
			new_status = DID_NO_CONNECT;
			break;
		case CAM_SCSI_BUS_RESET:
		case CAM_BDR_SENT:
			new_status = DID_RESET;
			break;
		case CAM_UNCOR_PARITY:
			new_status = DID_PARITY;
			break;
		case CAM_CMD_TIMEOUT:
			new_status = DID_TIME_OUT;
			break;
		case CAM_UA_ABORT:
		case CAM_REQ_CMP_ERR:
		case CAM_AUTOSENSE_FAIL:
		case CAM_NO_HBA:
		case CAM_DATA_RUN_ERR:
		case CAM_UNEXP_BUSFREE:
		case CAM_SEQUENCE_FAIL:
		case CAM_CCB_LEN_ERR:
		case CAM_PROVIDE_FAIL:
		case CAM_REQ_TERMIO:
		case CAM_UNREC_HBA_ERROR:
		case CAM_REQ_TOO_BIG:
			new_status = DID_ERROR;
			break;
		case CAM_REQUEUE_REQ:
			new_status = DID_REQUEUE;
			break;
		default:
			/* We should never get here */
			new_status = DID_ERROR;
			break;
		}

		ahc_cmd_set_transaction_status(cmd, new_status);
	}

	cmd->scsi_done(cmd);
}