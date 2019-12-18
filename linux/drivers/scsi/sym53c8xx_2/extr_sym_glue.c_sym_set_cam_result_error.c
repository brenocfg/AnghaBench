#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct sym_hcb {int dummy; } ;
struct sym_ccb {int ssss_status; int host_flags; int sv_scsi_status; int sv_resid; int /*<<< orphan*/  xerr_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  sns_bbuf; int /*<<< orphan*/  sv_xerr_status; struct scsi_cmnd* cmd; } ;
struct scsi_cmnd {int result; TYPE_1__* device; scalar_t__ sense_data; int /*<<< orphan*/  sense_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ABORT ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DRIVER_SENSE ; 
 int HF_SENSE ; 
 int /*<<< orphan*/  HS_COMPLETE ; 
 int /*<<< orphan*/  HS_SEL_TIMEOUT ; 
 int /*<<< orphan*/  HS_UNEXPECTED ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SYM_SNS_BBUF_LEN ; 
 int S_GOOD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  sym_clear_tasks (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sym_print_addr (struct scsi_cmnd*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_print_xerr (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_reset_scsi_target (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ sym_verbose ; 
 int sym_xerr_cam_status (int,int /*<<< orphan*/ ) ; 

void sym_set_cam_result_error(struct sym_hcb *np, struct sym_ccb *cp, int resid)
{
	struct scsi_cmnd *cmd = cp->cmd;
	u_int cam_status, scsi_status, drv_status;

	drv_status  = 0;
	cam_status  = DID_OK;
	scsi_status = cp->ssss_status;

	if (cp->host_flags & HF_SENSE) {
		scsi_status = cp->sv_scsi_status;
		resid = cp->sv_resid;
		if (sym_verbose && cp->sv_xerr_status)
			sym_print_xerr(cmd, cp->sv_xerr_status);
		if (cp->host_status == HS_COMPLETE &&
		    cp->ssss_status == S_GOOD &&
		    cp->xerr_status == 0) {
			cam_status = sym_xerr_cam_status(DID_OK,
							 cp->sv_xerr_status);
			drv_status = DRIVER_SENSE;
			/*
			 *  Bounce back the sense data to user.
			 */
			memset(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			memcpy(cmd->sense_buffer, cp->sns_bbuf,
			       min(SCSI_SENSE_BUFFERSIZE, SYM_SNS_BBUF_LEN));
#if 0
			/*
			 *  If the device reports a UNIT ATTENTION condition 
			 *  due to a RESET condition, we should consider all 
			 *  disconnect CCBs for this unit as aborted.
			 */
			if (1) {
				u_char *p;
				p  = (u_char *) cmd->sense_data;
				if (p[0]==0x70 && p[2]==0x6 && p[12]==0x29)
					sym_clear_tasks(np, DID_ABORT,
							cp->target,cp->lun, -1);
			}
#endif
		} else {
			/*
			 * Error return from our internal request sense.  This
			 * is bad: we must clear the contingent allegiance
			 * condition otherwise the device will always return
			 * BUSY.  Use a big stick.
			 */
			sym_reset_scsi_target(np, cmd->device->id);
			cam_status = DID_ERROR;
		}
	} else if (cp->host_status == HS_COMPLETE) 	/* Bad SCSI status */
		cam_status = DID_OK;
	else if (cp->host_status == HS_SEL_TIMEOUT)	/* Selection timeout */
		cam_status = DID_NO_CONNECT;
	else if (cp->host_status == HS_UNEXPECTED)	/* Unexpected BUS FREE*/
		cam_status = DID_ERROR;
	else {						/* Extended error */
		if (sym_verbose) {
			sym_print_addr(cmd, "COMMAND FAILED (%x %x %x).\n",
				cp->host_status, cp->ssss_status,
				cp->xerr_status);
		}
		/*
		 *  Set the most appropriate value for CAM status.
		 */
		cam_status = sym_xerr_cam_status(DID_ERROR, cp->xerr_status);
	}
	scsi_set_resid(cmd, resid);
	cmd->result = (drv_status << 24) | (cam_status << 16) | scsi_status;
}