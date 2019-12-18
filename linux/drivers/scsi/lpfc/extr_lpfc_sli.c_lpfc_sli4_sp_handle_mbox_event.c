#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_vport {int /*<<< orphan*/  vpi; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_mqe {int dummy; } ;
typedef  struct lpfc_mqe lpfc_mcqe ;
struct TYPE_16__ {int /*<<< orphan*/  mbx_wq; } ;
struct TYPE_15__ {TYPE_7__* mbox_active; int /*<<< orphan*/  sli_flag; int /*<<< orphan*/  mbox_tmo; } ;
struct lpfc_hba {TYPE_5__ sli4_hba; int /*<<< orphan*/  hbalock; TYPE_4__ sli; int /*<<< orphan*/  work_ha; TYPE_3__* pport; int /*<<< orphan*/  last_completion_time; TYPE_6__* mbox; } ;
struct lpfc_dmabuf {int dummy; } ;
struct TYPE_12__ {struct lpfc_mqe mqe; } ;
struct TYPE_18__ {int mbox_flag; struct lpfc_vport* vport; struct lpfc_nodelist* ctx_ndlp; struct lpfc_dmabuf* ctx_buf; scalar_t__ mbox_cmpl; TYPE_1__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/ * varWords; } ;
struct TYPE_17__ {TYPE_2__ un; } ;
struct TYPE_14__ {int /*<<< orphan*/  work_port_lock; int /*<<< orphan*/  work_port_events; } ;
typedef  TYPE_6__ MAILBOX_t ;
typedef  TYPE_7__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  HA_MBATT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_MBOX_VPORT ; 
 int LPFC_MBX_ERROR_RANGE ; 
 int LPFC_MBX_IMED_UNREG ; 
 int /*<<< orphan*/  LPFC_SLI_MBOX_ACTIVE ; 
 int MBX_BUSY ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 scalar_t__ MBX_SUCCESS ; 
 int MB_CQE_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WORKER_MBOX_TMO ; 
 int /*<<< orphan*/  __lpfc_mbox_cmpl_put (struct lpfc_hba*,TYPE_7__*) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_mqe*) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_mqe*,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_mbx_cmpl_dflt_rpi ; 
 int /*<<< orphan*/  lpfc_mcqe_status ; 
 int /*<<< orphan*/  lpfc_mqe_status ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_mq_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_pcimem_bcopy (TYPE_6__*,struct lpfc_mqe*,int) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_trailer_completed ; 
 int /*<<< orphan*/  lpfc_trailer_consumed ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_mbox_event(struct lpfc_hba *phba, struct lpfc_mcqe *mcqe)
{
	uint32_t mcqe_status;
	MAILBOX_t *mbox, *pmbox;
	struct lpfc_mqe *mqe;
	struct lpfc_vport *vport;
	struct lpfc_nodelist *ndlp;
	struct lpfc_dmabuf *mp;
	unsigned long iflags;
	LPFC_MBOXQ_t *pmb;
	bool workposted = false;
	int rc;

	/* If not a mailbox complete MCQE, out by checking mailbox consume */
	if (!bf_get(lpfc_trailer_completed, mcqe))
		goto out_no_mqe_complete;

	/* Get the reference to the active mbox command */
	spin_lock_irqsave(&phba->hbalock, iflags);
	pmb = phba->sli.mbox_active;
	if (unlikely(!pmb)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
				"1832 No pending MBOX command to handle\n");
		spin_unlock_irqrestore(&phba->hbalock, iflags);
		goto out_no_mqe_complete;
	}
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	mqe = &pmb->u.mqe;
	pmbox = (MAILBOX_t *)&pmb->u.mqe;
	mbox = phba->mbox;
	vport = pmb->vport;

	/* Reset heartbeat timer */
	phba->last_completion_time = jiffies;
	del_timer(&phba->sli.mbox_tmo);

	/* Move mbox data to caller's mailbox region, do endian swapping */
	if (pmb->mbox_cmpl && mbox)
		lpfc_sli4_pcimem_bcopy(mbox, mqe, sizeof(struct lpfc_mqe));

	/*
	 * For mcqe errors, conditionally move a modified error code to
	 * the mbox so that the error will not be missed.
	 */
	mcqe_status = bf_get(lpfc_mcqe_status, mcqe);
	if (mcqe_status != MB_CQE_STATUS_SUCCESS) {
		if (bf_get(lpfc_mqe_status, mqe) == MBX_SUCCESS)
			bf_set(lpfc_mqe_status, mqe,
			       (LPFC_MBX_ERROR_RANGE | mcqe_status));
	}
	if (pmb->mbox_flag & LPFC_MBX_IMED_UNREG) {
		pmb->mbox_flag &= ~LPFC_MBX_IMED_UNREG;
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_MBOX_VPORT,
				      "MBOX dflt rpi: status:x%x rpi:x%x",
				      mcqe_status,
				      pmbox->un.varWords[0], 0);
		if (mcqe_status == MB_CQE_STATUS_SUCCESS) {
			mp = (struct lpfc_dmabuf *)(pmb->ctx_buf);
			ndlp = (struct lpfc_nodelist *)pmb->ctx_ndlp;
			/* Reg_LOGIN of dflt RPI was successful. Now lets get
			 * RID of the PPI using the same mbox buffer.
			 */
			lpfc_unreg_login(phba, vport->vpi,
					 pmbox->un.varWords[0], pmb);
			pmb->mbox_cmpl = lpfc_mbx_cmpl_dflt_rpi;
			pmb->ctx_buf = mp;
			pmb->ctx_ndlp = ndlp;
			pmb->vport = vport;
			rc = lpfc_sli_issue_mbox(phba, pmb, MBX_NOWAIT);
			if (rc != MBX_BUSY)
				lpfc_printf_log(phba, KERN_ERR, LOG_MBOX |
						LOG_SLI, "0385 rc should "
						"have been MBX_BUSY\n");
			if (rc != MBX_NOT_FINISHED)
				goto send_current_mbox;
		}
	}
	spin_lock_irqsave(&phba->pport->work_port_lock, iflags);
	phba->pport->work_port_events &= ~WORKER_MBOX_TMO;
	spin_unlock_irqrestore(&phba->pport->work_port_lock, iflags);

	/* There is mailbox completion work to do */
	spin_lock_irqsave(&phba->hbalock, iflags);
	__lpfc_mbox_cmpl_put(phba, pmb);
	phba->work_ha |= HA_MBATT;
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	workposted = true;

send_current_mbox:
	spin_lock_irqsave(&phba->hbalock, iflags);
	/* Release the mailbox command posting token */
	phba->sli.sli_flag &= ~LPFC_SLI_MBOX_ACTIVE;
	/* Setting active mailbox pointer need to be in sync to flag clear */
	phba->sli.mbox_active = NULL;
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	/* Wake up worker thread to post the next pending mailbox command */
	lpfc_worker_wake_up(phba);
out_no_mqe_complete:
	if (bf_get(lpfc_trailer_consumed, mcqe))
		lpfc_sli4_mq_release(phba->sli4_hba.mbx_wq);
	return workposted;
}