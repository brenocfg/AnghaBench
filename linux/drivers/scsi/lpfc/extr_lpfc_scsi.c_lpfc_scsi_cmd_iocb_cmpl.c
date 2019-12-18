#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct scsi_dif_tuple {void* guard_tag; void* app_tag; scalar_t__ ref_tag; } ;
struct scsi_cmnd {scalar_t__* cmnd; int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  retries; TYPE_10__* device; scalar_t__ sense_buffer; } ;
struct lpfc_vport {int cfg_log_verbose; scalar_t__ cfg_max_scsicmpl_time; int /*<<< orphan*/  fc_myDID; } ;
struct lpfc_rport_data {struct lpfc_nodelist* pnode; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; scalar_t__ cmd_qdepth; int /*<<< orphan*/  last_change_time; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  nlp_nodename; int /*<<< orphan*/  nlp_portname; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_25__ {int /*<<< orphan*/  bgstat; } ;
struct TYPE_26__ {TYPE_6__ sli3_bg; } ;
struct TYPE_20__ {int* ulpWord; } ;
struct TYPE_27__ {int ulpStatus; TYPE_7__ unsli3; int /*<<< orphan*/  ulpContext; TYPE_1__ un; } ;
struct lpfc_iocbq {int iocb_flag; TYPE_8__ iocb; struct lpfc_vport* vport; scalar_t__ context1; } ;
struct TYPE_21__ {int /*<<< orphan*/  ulpIoTag; } ;
struct TYPE_16__ {int hba_wqidx; int sli4_xritag; int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/  sli4_lxritag; TYPE_2__ iocb; } ;
struct lpfc_io_buf {int result; int status; int exch_busy; int prot_data_type; int /*<<< orphan*/  buf_lock; scalar_t__ waitq; TYPE_11__ cur_iocbq; struct scsi_cmnd* pCmd; scalar_t__ start_time; TYPE_9__* fcp_rsp; int /*<<< orphan*/ * prot_data_segment; scalar_t__ prot_data; struct lpfc_rport_data* rdata; } ;
struct TYPE_18__ {TYPE_12__* hdwq; } ;
struct lpfc_hba {int cpucheck_on; scalar_t__ sli_rev; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  work_list; TYPE_13__ sli4_hba; } ;
struct TYPE_24__ {int /*<<< orphan*/  evt_listp; int /*<<< orphan*/  evt; } ;
struct TYPE_22__ {int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  subcategory; int /*<<< orphan*/  event_type; } ;
struct TYPE_23__ {TYPE_3__ fabric_evt; } ;
struct lpfc_fast_path_event {TYPE_5__ work_evt; struct lpfc_vport* vport; TYPE_4__ un; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_28__ {int rspStatus2; scalar_t__ rspSnsLen; int /*<<< orphan*/  rspStatus3; } ;
struct TYPE_19__ {int /*<<< orphan*/  io_cmpls; } ;
struct TYPE_17__ {int /*<<< orphan*/ * cpucheck_cmpl_io; TYPE_14__ scsi_cstat; } ;
struct TYPE_15__ {int id; int lun; struct Scsi_Host* host; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_REQUEUE ; 
 int DID_TRANSPORT_DISRUPTED ; 
 int /*<<< orphan*/  FC_REG_FABRIC_EVENT ; 
 int IOERR_ABORT_REQUESTED ; 
 int IOERR_DRVR_MASK ; 
 int IOERR_ELXSEC_CRYPTO_COMPARE_ERROR ; 
 int IOERR_ELXSEC_CRYPTO_ERROR ; 
 int IOERR_ELXSEC_KEY_UNWRAP_COMPARE_ERROR ; 
 int IOERR_ELXSEC_KEY_UNWRAP_ERROR ; 
 int IOERR_INVALID_RPI ; 
 int IOERR_NO_RESOURCES ; 
 int IOERR_PARAM_MASK ; 
 int IOERR_RX_DMA_FAILED ; 
 int IOERR_SLER_CMD_RCV_FAILURE ; 
 int IOERR_TX_DMA_FAILED ; 
 int IOSTAT_CNT ; 
 int IOSTAT_DEFAULT ; 
 int IOSTAT_DRIVER_REJECT ; 
#define  IOSTAT_FABRIC_BSY 135 
#define  IOSTAT_FCP_RSP_ERROR 134 
#define  IOSTAT_LOCAL_REJECT 133 
#define  IOSTAT_NPORT_BSY 132 
#define  IOSTAT_REMOTE_STOP 131 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_BG ; 
 int LOG_FCP ; 
 int LOG_FCP_UNDER ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_CHECK_CPU_CNT ; 
 int LPFC_CHECK_SCSI_IO ; 
 int /*<<< orphan*/  LPFC_DRIVER_ABORTED ; 
 int /*<<< orphan*/  LPFC_EVENT_FABRIC_BUSY ; 
 int /*<<< orphan*/  LPFC_EVENT_PORT_BUSY ; 
 int /*<<< orphan*/  LPFC_EVT_FASTPATH_MGMT_EVT ; 
 int LPFC_EXCHANGE_BUSY ; 
#define  LPFC_INJERR_APPTAG 130 
#define  LPFC_INJERR_GUARD 129 
#define  LPFC_INJERR_REFTAG 128 
 scalar_t__ LPFC_MIN_TGT_QDEPTH ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ READ_10 ; 
 int RESID_UNDER ; 
 int SAM_STAT_BUSY ; 
 int /*<<< orphan*/  SCSI_PROT_NORMAL ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lpfc_fast_path_event* lpfc_alloc_fast_evt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_handle_fcp_err (struct lpfc_vport*,struct lpfc_io_buf*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_parse_bg_err (struct lpfc_hba*,struct lpfc_io_buf*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  lpfc_release_scsi_buf (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 int /*<<< orphan*/  lpfc_scsi_unprep_dma_buf (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 int /*<<< orphan*/  lpfc_set_rrq_active (struct lpfc_hba*,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_update_stats (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  scsi_get_prot_op (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (scalar_t__) ; 

__attribute__((used)) static void
lpfc_scsi_cmd_iocb_cmpl(struct lpfc_hba *phba, struct lpfc_iocbq *pIocbIn,
			struct lpfc_iocbq *pIocbOut)
{
	struct lpfc_io_buf *lpfc_cmd =
		(struct lpfc_io_buf *) pIocbIn->context1;
	struct lpfc_vport      *vport = pIocbIn->vport;
	struct lpfc_rport_data *rdata = lpfc_cmd->rdata;
	struct lpfc_nodelist *pnode = rdata->pnode;
	struct scsi_cmnd *cmd;
	unsigned long flags;
	struct lpfc_fast_path_event *fast_path_evt;
	struct Scsi_Host *shost;
	int idx;
	uint32_t logit = LOG_FCP;
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	int cpu;
#endif

	/* Guard against abort handler being called at same time */
	spin_lock(&lpfc_cmd->buf_lock);

	/* Sanity check on return of outstanding command */
	cmd = lpfc_cmd->pCmd;
	if (!cmd) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "2621 IO completion: Not an active IO\n");
		spin_unlock(&lpfc_cmd->buf_lock);
		return;
	}

	idx = lpfc_cmd->cur_iocbq.hba_wqidx;
	if (phba->sli4_hba.hdwq)
		phba->sli4_hba.hdwq[idx].scsi_cstat.io_cmpls++;

#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	if (phba->cpucheck_on & LPFC_CHECK_SCSI_IO) {
		cpu = raw_smp_processor_id();
		if (cpu < LPFC_CHECK_CPU_CNT && phba->sli4_hba.hdwq)
			phba->sli4_hba.hdwq[idx].cpucheck_cmpl_io[cpu]++;
	}
#endif
	shost = cmd->device->host;

	lpfc_cmd->result = (pIocbOut->iocb.un.ulpWord[4] & IOERR_PARAM_MASK);
	lpfc_cmd->status = pIocbOut->iocb.ulpStatus;
	/* pick up SLI4 exhange busy status from HBA */
	lpfc_cmd->exch_busy = pIocbOut->iocb_flag & LPFC_EXCHANGE_BUSY;

#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	if (lpfc_cmd->prot_data_type) {
		struct scsi_dif_tuple *src = NULL;

		src =  (struct scsi_dif_tuple *)lpfc_cmd->prot_data_segment;
		/*
		 * Used to restore any changes to protection
		 * data for error injection.
		 */
		switch (lpfc_cmd->prot_data_type) {
		case LPFC_INJERR_REFTAG:
			src->ref_tag =
				lpfc_cmd->prot_data;
			break;
		case LPFC_INJERR_APPTAG:
			src->app_tag =
				(uint16_t)lpfc_cmd->prot_data;
			break;
		case LPFC_INJERR_GUARD:
			src->guard_tag =
				(uint16_t)lpfc_cmd->prot_data;
			break;
		default:
			break;
		}

		lpfc_cmd->prot_data = 0;
		lpfc_cmd->prot_data_type = 0;
		lpfc_cmd->prot_data_segment = NULL;
	}
#endif

	if (lpfc_cmd->status) {
		if (lpfc_cmd->status == IOSTAT_LOCAL_REJECT &&
		    (lpfc_cmd->result & IOERR_DRVR_MASK))
			lpfc_cmd->status = IOSTAT_DRIVER_REJECT;
		else if (lpfc_cmd->status >= IOSTAT_CNT)
			lpfc_cmd->status = IOSTAT_DEFAULT;
		if (lpfc_cmd->status == IOSTAT_FCP_RSP_ERROR &&
		    !lpfc_cmd->fcp_rsp->rspStatus3 &&
		    (lpfc_cmd->fcp_rsp->rspStatus2 & RESID_UNDER) &&
		    !(vport->cfg_log_verbose & LOG_FCP_UNDER))
			logit = 0;
		else
			logit = LOG_FCP | LOG_FCP_UNDER;
		lpfc_printf_vlog(vport, KERN_WARNING, logit,
			 "9030 FCP cmd x%x failed <%d/%lld> "
			 "status: x%x result: x%x "
			 "sid: x%x did: x%x oxid: x%x "
			 "Data: x%x x%x\n",
			 cmd->cmnd[0],
			 cmd->device ? cmd->device->id : 0xffff,
			 cmd->device ? cmd->device->lun : 0xffff,
			 lpfc_cmd->status, lpfc_cmd->result,
			 vport->fc_myDID,
			 (pnode) ? pnode->nlp_DID : 0,
			 phba->sli_rev == LPFC_SLI_REV4 ?
			     lpfc_cmd->cur_iocbq.sli4_xritag : 0xffff,
			 pIocbOut->iocb.ulpContext,
			 lpfc_cmd->cur_iocbq.iocb.ulpIoTag);

		switch (lpfc_cmd->status) {
		case IOSTAT_FCP_RSP_ERROR:
			/* Call FCP RSP handler to determine result */
			lpfc_handle_fcp_err(vport, lpfc_cmd, pIocbOut);
			break;
		case IOSTAT_NPORT_BSY:
		case IOSTAT_FABRIC_BSY:
			cmd->result = DID_TRANSPORT_DISRUPTED << 16;
			fast_path_evt = lpfc_alloc_fast_evt(phba);
			if (!fast_path_evt)
				break;
			fast_path_evt->un.fabric_evt.event_type =
				FC_REG_FABRIC_EVENT;
			fast_path_evt->un.fabric_evt.subcategory =
				(lpfc_cmd->status == IOSTAT_NPORT_BSY) ?
				LPFC_EVENT_PORT_BUSY : LPFC_EVENT_FABRIC_BUSY;
			if (pnode && NLP_CHK_NODE_ACT(pnode)) {
				memcpy(&fast_path_evt->un.fabric_evt.wwpn,
					&pnode->nlp_portname,
					sizeof(struct lpfc_name));
				memcpy(&fast_path_evt->un.fabric_evt.wwnn,
					&pnode->nlp_nodename,
					sizeof(struct lpfc_name));
			}
			fast_path_evt->vport = vport;
			fast_path_evt->work_evt.evt =
				LPFC_EVT_FASTPATH_MGMT_EVT;
			spin_lock_irqsave(&phba->hbalock, flags);
			list_add_tail(&fast_path_evt->work_evt.evt_listp,
				&phba->work_list);
			spin_unlock_irqrestore(&phba->hbalock, flags);
			lpfc_worker_wake_up(phba);
			break;
		case IOSTAT_LOCAL_REJECT:
		case IOSTAT_REMOTE_STOP:
			if (lpfc_cmd->result == IOERR_ELXSEC_KEY_UNWRAP_ERROR ||
			    lpfc_cmd->result ==
					IOERR_ELXSEC_KEY_UNWRAP_COMPARE_ERROR ||
			    lpfc_cmd->result == IOERR_ELXSEC_CRYPTO_ERROR ||
			    lpfc_cmd->result ==
					IOERR_ELXSEC_CRYPTO_COMPARE_ERROR) {
				cmd->result = DID_NO_CONNECT << 16;
				break;
			}
			if (lpfc_cmd->result == IOERR_INVALID_RPI ||
			    lpfc_cmd->result == IOERR_NO_RESOURCES ||
			    lpfc_cmd->result == IOERR_ABORT_REQUESTED ||
			    lpfc_cmd->result == IOERR_SLER_CMD_RCV_FAILURE) {
				cmd->result = DID_REQUEUE << 16;
				break;
			}
			if ((lpfc_cmd->result == IOERR_RX_DMA_FAILED ||
			     lpfc_cmd->result == IOERR_TX_DMA_FAILED) &&
			     pIocbOut->iocb.unsli3.sli3_bg.bgstat) {
				if (scsi_get_prot_op(cmd) != SCSI_PROT_NORMAL) {
					/*
					 * This is a response for a BG enabled
					 * cmd. Parse BG error
					 */
					lpfc_parse_bg_err(phba, lpfc_cmd,
							pIocbOut);
					break;
				} else {
					lpfc_printf_vlog(vport, KERN_WARNING,
							LOG_BG,
							"9031 non-zero BGSTAT "
							"on unprotected cmd\n");
				}
			}
			if ((lpfc_cmd->status == IOSTAT_REMOTE_STOP)
				&& (phba->sli_rev == LPFC_SLI_REV4)
				&& (pnode && NLP_CHK_NODE_ACT(pnode))) {
				/* This IO was aborted by the target, we don't
				 * know the rxid and because we did not send the
				 * ABTS we cannot generate and RRQ.
				 */
				lpfc_set_rrq_active(phba, pnode,
					lpfc_cmd->cur_iocbq.sli4_lxritag,
					0, 0);
			}
			/* fall through */
		default:
			cmd->result = DID_ERROR << 16;
			break;
		}

		if (!pnode || !NLP_CHK_NODE_ACT(pnode)
		    || (pnode->nlp_state != NLP_STE_MAPPED_NODE))
			cmd->result = DID_TRANSPORT_DISRUPTED << 16 |
				      SAM_STAT_BUSY;
	} else
		cmd->result = DID_OK << 16;

	if (cmd->result || lpfc_cmd->fcp_rsp->rspSnsLen) {
		uint32_t *lp = (uint32_t *)cmd->sense_buffer;

		lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
				 "0710 Iodone <%d/%llu> cmd x%px, error "
				 "x%x SNS x%x x%x Data: x%x x%x\n",
				 cmd->device->id, cmd->device->lun, cmd,
				 cmd->result, *lp, *(lp + 3), cmd->retries,
				 scsi_get_resid(cmd));
	}

	lpfc_update_stats(phba, lpfc_cmd);
	if (vport->cfg_max_scsicmpl_time &&
	   time_after(jiffies, lpfc_cmd->start_time +
		msecs_to_jiffies(vport->cfg_max_scsicmpl_time))) {
		spin_lock_irqsave(shost->host_lock, flags);
		if (pnode && NLP_CHK_NODE_ACT(pnode)) {
			if (pnode->cmd_qdepth >
				atomic_read(&pnode->cmd_pending) &&
				(atomic_read(&pnode->cmd_pending) >
				LPFC_MIN_TGT_QDEPTH) &&
				((cmd->cmnd[0] == READ_10) ||
				(cmd->cmnd[0] == WRITE_10)))
				pnode->cmd_qdepth =
					atomic_read(&pnode->cmd_pending);

			pnode->last_change_time = jiffies;
		}
		spin_unlock_irqrestore(shost->host_lock, flags);
	}
	lpfc_scsi_unprep_dma_buf(phba, lpfc_cmd);

	lpfc_cmd->pCmd = NULL;
	spin_unlock(&lpfc_cmd->buf_lock);

	/* The sdev is not guaranteed to be valid post scsi_done upcall. */
	cmd->scsi_done(cmd);

	/*
	 * If there is an abort thread waiting for command completion
	 * wake up the thread.
	 */
	spin_lock(&lpfc_cmd->buf_lock);
	lpfc_cmd->cur_iocbq.iocb_flag &= ~LPFC_DRIVER_ABORTED;
	if (lpfc_cmd->waitq)
		wake_up(lpfc_cmd->waitq);
	spin_unlock(&lpfc_cmd->buf_lock);

	lpfc_release_scsi_buf(phba, lpfc_cmd);
}