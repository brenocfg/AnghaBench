#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  vpi_state; } ;
struct lpfc_nodelist {int nlp_flag; scalar_t__ nlp_defer_did; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_rpi; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_3__* pport; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  vpi; } ;
struct TYPE_13__ {TYPE_1__ varRegLogin; int /*<<< orphan*/ * varWords; } ;
struct TYPE_15__ {scalar_t__ mbxCommand; scalar_t__ mbxStatus; TYPE_2__ un; } ;
struct TYPE_16__ {int /*<<< orphan*/  mqe; TYPE_4__ mb; } ;
struct TYPE_17__ {void (* mbox_cmpl ) (struct lpfc_hba*,TYPE_6__*) ;TYPE_5__ u; int /*<<< orphan*/ * ctx_ndlp; int /*<<< orphan*/ * ctx_buf; struct lpfc_vport* vport; } ;
struct TYPE_14__ {int load_flag; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_UNLOADING ; 
 int /*<<< orphan*/  FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_DISCOVERY ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int /*<<< orphan*/  LPFC_VPI_REGISTERED ; 
 scalar_t__ MBXERR_SEC_NO_PERMISSION ; 
 scalar_t__ MBX_INIT_LINK ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 scalar_t__ MBX_REG_LOGIN64 ; 
 scalar_t__ MBX_REG_VPI ; 
 scalar_t__ MBX_SLI4_CONFIG ; 
 scalar_t__ MBX_UNREG_LOGIN ; 
 scalar_t__ NLP_EVT_NOTHING_PENDING ; 
 int NLP_UNREG_INP ; 
 int /*<<< orphan*/  __lpfc_sli_rpi_release (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mqe_command ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,struct lpfc_nodelist*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,TYPE_6__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_sli_def_mbox_cmpl(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport  *vport = pmb->vport;
	struct lpfc_dmabuf *mp;
	struct lpfc_nodelist *ndlp;
	struct Scsi_Host *shost;
	uint16_t rpi, vpi;
	int rc;

	mp = (struct lpfc_dmabuf *)(pmb->ctx_buf);

	if (mp) {
		lpfc_mbuf_free(phba, mp->virt, mp->phys);
		kfree(mp);
	}

	/*
	 * If a REG_LOGIN succeeded  after node is destroyed or node
	 * is in re-discovery driver need to cleanup the RPI.
	 */
	if (!(phba->pport->load_flag & FC_UNLOADING) &&
	    pmb->u.mb.mbxCommand == MBX_REG_LOGIN64 &&
	    !pmb->u.mb.mbxStatus) {
		rpi = pmb->u.mb.un.varWords[0];
		vpi = pmb->u.mb.un.varRegLogin.vpi;
		lpfc_unreg_login(phba, vpi, rpi, pmb);
		pmb->vport = vport;
		pmb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		rc = lpfc_sli_issue_mbox(phba, pmb, MBX_NOWAIT);
		if (rc != MBX_NOT_FINISHED)
			return;
	}

	if ((pmb->u.mb.mbxCommand == MBX_REG_VPI) &&
		!(phba->pport->load_flag & FC_UNLOADING) &&
		!pmb->u.mb.mbxStatus) {
		shost = lpfc_shost_from_vport(vport);
		spin_lock_irq(shost->host_lock);
		vport->vpi_state |= LPFC_VPI_REGISTERED;
		vport->fc_flag &= ~FC_VPORT_NEEDS_REG_VPI;
		spin_unlock_irq(shost->host_lock);
	}

	if (pmb->u.mb.mbxCommand == MBX_REG_LOGIN64) {
		ndlp = (struct lpfc_nodelist *)pmb->ctx_ndlp;
		lpfc_nlp_put(ndlp);
		pmb->ctx_buf = NULL;
		pmb->ctx_ndlp = NULL;
	}

	if (pmb->u.mb.mbxCommand == MBX_UNREG_LOGIN) {
		ndlp = (struct lpfc_nodelist *)pmb->ctx_ndlp;

		/* Check to see if there are any deferred events to process */
		if (ndlp) {
			lpfc_printf_vlog(
				vport,
				KERN_INFO, LOG_MBOX | LOG_DISCOVERY,
				"1438 UNREG cmpl deferred mbox x%x "
				"on NPort x%x Data: x%x x%x %px\n",
				ndlp->nlp_rpi, ndlp->nlp_DID,
				ndlp->nlp_flag, ndlp->nlp_defer_did, ndlp);

			if ((ndlp->nlp_flag & NLP_UNREG_INP) &&
			    (ndlp->nlp_defer_did != NLP_EVT_NOTHING_PENDING)) {
				ndlp->nlp_flag &= ~NLP_UNREG_INP;
				ndlp->nlp_defer_did = NLP_EVT_NOTHING_PENDING;
				lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0);
			} else {
				__lpfc_sli_rpi_release(vport, ndlp);
			}
			pmb->ctx_ndlp = NULL;
		}
	}

	/* Check security permission status on INIT_LINK mailbox command */
	if ((pmb->u.mb.mbxCommand == MBX_INIT_LINK) &&
	    (pmb->u.mb.mbxStatus == MBXERR_SEC_NO_PERMISSION))
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
				"2860 SLI authentication is required "
				"for INIT_LINK but has not done yet\n");

	if (bf_get(lpfc_mqe_command, &pmb->u.mqe) == MBX_SLI4_CONFIG)
		lpfc_sli4_mbox_cmd_free(phba, pmb);
	else
		mempool_free(pmb, phba->mbox_mem_pool);
}