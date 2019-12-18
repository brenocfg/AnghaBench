#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct scsi_cmnd {int underflow; scalar_t__ sc_data_direction; int result; int /*<<< orphan*/ * cmnd; scalar_t__ sense_buffer; TYPE_3__* device; } ;
struct lpfc_vport {int cfg_log_verbose; struct lpfc_hba* phba; } ;
struct TYPE_6__ {int fcpi_parm; } ;
struct TYPE_7__ {TYPE_1__ fcpi; } ;
struct TYPE_10__ {int /*<<< orphan*/  ulpContext; TYPE_2__ un; } ;
struct lpfc_iocbq {TYPE_5__ iocb; } ;
struct TYPE_9__ {int /*<<< orphan*/  sli4_xritag; } ;
struct lpfc_io_buf {TYPE_4__ cur_iocbq; struct fcp_rsp* fcp_rsp; struct fcp_cmnd* fcp_cmnd; struct scsi_cmnd* pCmd; } ;
struct lpfc_hba {scalar_t__ sli_rev; } ;
struct fcp_rsp {int rspStatus2; int rspStatus3; int rspRspLen; int rspSnsLen; int rspResId; int /*<<< orphan*/  rspInfo3; int /*<<< orphan*/  rspInfo0; } ;
struct fcp_cmnd {int fcpDl; scalar_t__ fcpCntl2; } ;
struct TYPE_8__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int DID_OK ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_FCP ; 
 int LOG_FCP_ERROR ; 
 int LOG_FCP_UNDER ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int RESID_OVER ; 
 int RESID_UNDER ; 
 int RSP_LEN_VALID ; 
 int /*<<< orphan*/  RSP_NO_FAILURE ; 
#define  SAM_STAT_CHECK_CONDITION 129 
#define  SAM_STAT_GOOD 128 
 int SCSI_SENSE_BUFFERSIZE ; 
 int SNS_LEN_VALID ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  lpfc_send_scsi_error_event (struct lpfc_hba*,struct lpfc_vport*,struct lpfc_io_buf*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 

__attribute__((used)) static void
lpfc_handle_fcp_err(struct lpfc_vport *vport, struct lpfc_io_buf *lpfc_cmd,
		    struct lpfc_iocbq *rsp_iocb)
{
	struct lpfc_hba *phba = vport->phba;
	struct scsi_cmnd *cmnd = lpfc_cmd->pCmd;
	struct fcp_cmnd *fcpcmd = lpfc_cmd->fcp_cmnd;
	struct fcp_rsp *fcprsp = lpfc_cmd->fcp_rsp;
	uint32_t fcpi_parm = rsp_iocb->iocb.un.fcpi.fcpi_parm;
	uint32_t resp_info = fcprsp->rspStatus2;
	uint32_t scsi_status = fcprsp->rspStatus3;
	uint32_t *lp;
	uint32_t host_status = DID_OK;
	uint32_t rsplen = 0;
	uint32_t fcpDl;
	uint32_t logit = LOG_FCP | LOG_FCP_ERROR;


	/*
	 *  If this is a task management command, there is no
	 *  scsi packet associated with this lpfc_cmd.  The driver
	 *  consumes it.
	 */
	if (fcpcmd->fcpCntl2) {
		scsi_status = 0;
		goto out;
	}

	if (resp_info & RSP_LEN_VALID) {
		rsplen = be32_to_cpu(fcprsp->rspRspLen);
		if (rsplen != 0 && rsplen != 4 && rsplen != 8) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
				 "2719 Invalid response length: "
				 "tgt x%x lun x%llx cmnd x%x rsplen x%x\n",
				 cmnd->device->id,
				 cmnd->device->lun, cmnd->cmnd[0],
				 rsplen);
			host_status = DID_ERROR;
			goto out;
		}
		if (fcprsp->rspInfo3 != RSP_NO_FAILURE) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
				 "2757 Protocol failure detected during "
				 "processing of FCP I/O op: "
				 "tgt x%x lun x%llx cmnd x%x rspInfo3 x%x\n",
				 cmnd->device->id,
				 cmnd->device->lun, cmnd->cmnd[0],
				 fcprsp->rspInfo3);
			host_status = DID_ERROR;
			goto out;
		}
	}

	if ((resp_info & SNS_LEN_VALID) && fcprsp->rspSnsLen) {
		uint32_t snslen = be32_to_cpu(fcprsp->rspSnsLen);
		if (snslen > SCSI_SENSE_BUFFERSIZE)
			snslen = SCSI_SENSE_BUFFERSIZE;

		if (resp_info & RSP_LEN_VALID)
		  rsplen = be32_to_cpu(fcprsp->rspRspLen);
		memcpy(cmnd->sense_buffer, &fcprsp->rspInfo0 + rsplen, snslen);
	}
	lp = (uint32_t *)cmnd->sense_buffer;

	/* special handling for under run conditions */
	if (!scsi_status && (resp_info & RESID_UNDER)) {
		/* don't log under runs if fcp set... */
		if (vport->cfg_log_verbose & LOG_FCP)
			logit = LOG_FCP_ERROR;
		/* unless operator says so */
		if (vport->cfg_log_verbose & LOG_FCP_UNDER)
			logit = LOG_FCP_UNDER;
	}

	lpfc_printf_vlog(vport, KERN_WARNING, logit,
			 "9024 FCP command x%x failed: x%x SNS x%x x%x "
			 "Data: x%x x%x x%x x%x x%x\n",
			 cmnd->cmnd[0], scsi_status,
			 be32_to_cpu(*lp), be32_to_cpu(*(lp + 3)), resp_info,
			 be32_to_cpu(fcprsp->rspResId),
			 be32_to_cpu(fcprsp->rspSnsLen),
			 be32_to_cpu(fcprsp->rspRspLen),
			 fcprsp->rspInfo3);

	scsi_set_resid(cmnd, 0);
	fcpDl = be32_to_cpu(fcpcmd->fcpDl);
	if (resp_info & RESID_UNDER) {
		scsi_set_resid(cmnd, be32_to_cpu(fcprsp->rspResId));

		lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP_UNDER,
				 "9025 FCP Underrun, expected %d, "
				 "residual %d Data: x%x x%x x%x\n",
				 fcpDl,
				 scsi_get_resid(cmnd), fcpi_parm, cmnd->cmnd[0],
				 cmnd->underflow);

		/*
		 * If there is an under run, check if under run reported by
		 * storage array is same as the under run reported by HBA.
		 * If this is not same, there is a dropped frame.
		 */
		if (fcpi_parm && (scsi_get_resid(cmnd) != fcpi_parm)) {
			lpfc_printf_vlog(vport, KERN_WARNING,
					 LOG_FCP | LOG_FCP_ERROR,
					 "9026 FCP Read Check Error "
					 "and Underrun Data: x%x x%x x%x x%x\n",
					 fcpDl,
					 scsi_get_resid(cmnd), fcpi_parm,
					 cmnd->cmnd[0]);
			scsi_set_resid(cmnd, scsi_bufflen(cmnd));
			host_status = DID_ERROR;
		}
		/*
		 * The cmnd->underflow is the minimum number of bytes that must
		 * be transferred for this command.  Provided a sense condition
		 * is not present, make sure the actual amount transferred is at
		 * least the underflow value or fail.
		 */
		if (!(resp_info & SNS_LEN_VALID) &&
		    (scsi_status == SAM_STAT_GOOD) &&
		    (scsi_bufflen(cmnd) - scsi_get_resid(cmnd)
		     < cmnd->underflow)) {
			lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
					 "9027 FCP command x%x residual "
					 "underrun converted to error "
					 "Data: x%x x%x x%x\n",
					 cmnd->cmnd[0], scsi_bufflen(cmnd),
					 scsi_get_resid(cmnd), cmnd->underflow);
			host_status = DID_ERROR;
		}
	} else if (resp_info & RESID_OVER) {
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP,
				 "9028 FCP command x%x residual overrun error. "
				 "Data: x%x x%x\n", cmnd->cmnd[0],
				 scsi_bufflen(cmnd), scsi_get_resid(cmnd));
		host_status = DID_ERROR;

	/*
	 * Check SLI validation that all the transfer was actually done
	 * (fcpi_parm should be zero). Apply check only to reads.
	 */
	} else if (fcpi_parm) {
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_FCP | LOG_FCP_ERROR,
				 "9029 FCP %s Check Error xri x%x  Data: "
				 "x%x x%x x%x x%x x%x\n",
				 ((cmnd->sc_data_direction == DMA_FROM_DEVICE) ?
				 "Read" : "Write"),
				 ((phba->sli_rev == LPFC_SLI_REV4) ?
				 lpfc_cmd->cur_iocbq.sli4_xritag :
				 rsp_iocb->iocb.ulpContext),
				 fcpDl, be32_to_cpu(fcprsp->rspResId),
				 fcpi_parm, cmnd->cmnd[0], scsi_status);

		/* There is some issue with the LPe12000 that causes it
		 * to miscalculate the fcpi_parm and falsely trip this
		 * recovery logic.  Detect this case and don't error when true.
		 */
		if (fcpi_parm > fcpDl)
			goto out;

		switch (scsi_status) {
		case SAM_STAT_GOOD:
		case SAM_STAT_CHECK_CONDITION:
			/* Fabric dropped a data frame. Fail any successful
			 * command in which we detected dropped frames.
			 * A status of good or some check conditions could
			 * be considered a successful command.
			 */
			host_status = DID_ERROR;
			break;
		}
		scsi_set_resid(cmnd, scsi_bufflen(cmnd));
	}

 out:
	cmnd->result = host_status << 16 | scsi_status;
	lpfc_send_scsi_error_event(vport->phba, vport, lpfc_cmd, rsp_iocb);
}