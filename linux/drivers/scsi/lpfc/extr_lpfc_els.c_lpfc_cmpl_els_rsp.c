#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {int fc_flag; } ;
struct lpfc_nodelist {int nlp_flag; scalar_t__ nlp_state; int nlp_rpi; int nlp_prev_state; int /*<<< orphan*/  nlp_DID; struct lpfc_vport* vport; } ;
struct TYPE_10__ {int /*<<< orphan*/  remoteID; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ulpWord; TYPE_2__ elsreq64; } ;
struct TYPE_13__ {scalar_t__ ulpStatus; int /*<<< orphan*/  ulpTimeout; TYPE_3__ un; int /*<<< orphan*/  ulpIoTag; } ;
struct TYPE_9__ {TYPE_4__* mbox; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context1; TYPE_5__ iocb; scalar_t__ context2; TYPE_1__ context_un; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_12__ {struct lpfc_dmabuf* ctx_buf; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  mbox_flag; struct lpfc_vport* vport; int /*<<< orphan*/  ctx_ndlp; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;
typedef  TYPE_5__ IOCB_t ;

/* Variables and functions */
 scalar_t__ ELS_CMD_LS_RJT ; 
 int FC_PT2PT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_RSP ; 
 int /*<<< orphan*/  LPFC_MBX_IMED_UNREG ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int NLP_ACC_REGLOGIN ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int NLP_REG_LOGIN_SEND ; 
 int NLP_RM_DFLT_RPI ; 
 scalar_t__ NLP_STE_PLOGI_ISSUE ; 
 scalar_t__ NLP_STE_REG_LOGIN_ISSUE ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_error_lost_link (TYPE_5__*) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_dflt_rpi ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_reg_login ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 scalar_t__ lpfc_nlp_not_used (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_rpi (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_els_rsp(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		  struct lpfc_iocbq *rspiocb)
{
	struct lpfc_nodelist *ndlp = (struct lpfc_nodelist *) cmdiocb->context1;
	struct lpfc_vport *vport = ndlp ? ndlp->vport : NULL;
	struct Scsi_Host  *shost = vport ? lpfc_shost_from_vport(vport) : NULL;
	IOCB_t  *irsp;
	uint8_t *pcmd;
	LPFC_MBOXQ_t *mbox = NULL;
	struct lpfc_dmabuf *mp = NULL;
	uint32_t ls_rjt = 0;

	irsp = &rspiocb->iocb;

	if (cmdiocb->context_un.mbox)
		mbox = cmdiocb->context_un.mbox;

	/* First determine if this is a LS_RJT cmpl. Note, this callback
	 * function can have cmdiocb->contest1 (ndlp) field set to NULL.
	 */
	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) cmdiocb->context2)->virt);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
	    (*((uint32_t *) (pcmd)) == ELS_CMD_LS_RJT)) {
		/* A LS_RJT associated with Default RPI cleanup has its own
		 * separate code path.
		 */
		if (!(ndlp->nlp_flag & NLP_RM_DFLT_RPI))
			ls_rjt = 1;
	}

	/* Check to see if link went down during discovery */
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp) || lpfc_els_chk_latt(vport)) {
		if (mbox) {
			mp = (struct lpfc_dmabuf *)mbox->ctx_buf;
			if (mp) {
				lpfc_mbuf_free(phba, mp->virt, mp->phys);
				kfree(mp);
			}
			mempool_free(mbox, phba->mbox_mem_pool);
		}
		if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
		    (ndlp->nlp_flag & NLP_RM_DFLT_RPI))
			if (lpfc_nlp_not_used(ndlp)) {
				ndlp = NULL;
				/* Indicate the node has already released,
				 * should not reference to it from within
				 * the routine lpfc_els_free_iocb.
				 */
				cmdiocb->context1 = NULL;
			}
		goto out;
	}

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
		"ELS rsp cmpl:    status:x%x/x%x did:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4],
		cmdiocb->iocb.un.elsreq64.remoteID);
	/* ELS response tag <ulpIoTag> completes */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0110 ELS response tag x%x completes "
			 "Data: x%x x%x x%x x%x x%x x%x x%x\n",
			 cmdiocb->iocb.ulpIoTag, rspiocb->iocb.ulpStatus,
			 rspiocb->iocb.un.ulpWord[4], rspiocb->iocb.ulpTimeout,
			 ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_state,
			 ndlp->nlp_rpi);
	if (mbox) {
		if ((rspiocb->iocb.ulpStatus == 0)
		    && (ndlp->nlp_flag & NLP_ACC_REGLOGIN)) {
			if (!lpfc_unreg_rpi(vport, ndlp) &&
			    (!(vport->fc_flag & FC_PT2PT)) &&
			    (ndlp->nlp_state ==  NLP_STE_PLOGI_ISSUE ||
			     ndlp->nlp_state == NLP_STE_REG_LOGIN_ISSUE)) {
				lpfc_printf_vlog(vport, KERN_INFO,
					LOG_DISCOVERY,
					"0314 PLOGI recov DID x%x "
					"Data: x%x x%x x%x\n",
					ndlp->nlp_DID, ndlp->nlp_state,
					ndlp->nlp_rpi, ndlp->nlp_flag);
				mp = mbox->ctx_buf;
				if (mp) {
					lpfc_mbuf_free(phba, mp->virt,
						       mp->phys);
					kfree(mp);
				}
				mempool_free(mbox, phba->mbox_mem_pool);
				goto out;
			}

			/* Increment reference count to ndlp to hold the
			 * reference to ndlp for the callback function.
			 */
			mbox->ctx_ndlp = lpfc_nlp_get(ndlp);
			mbox->vport = vport;
			if (ndlp->nlp_flag & NLP_RM_DFLT_RPI) {
				mbox->mbox_flag |= LPFC_MBX_IMED_UNREG;
				mbox->mbox_cmpl = lpfc_mbx_cmpl_dflt_rpi;
			}
			else {
				mbox->mbox_cmpl = lpfc_mbx_cmpl_reg_login;
				ndlp->nlp_prev_state = ndlp->nlp_state;
				lpfc_nlp_set_state(vport, ndlp,
					   NLP_STE_REG_LOGIN_ISSUE);
			}

			ndlp->nlp_flag |= NLP_REG_LOGIN_SEND;
			if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT)
			    != MBX_NOT_FINISHED)
				goto out;

			/* Decrement the ndlp reference count we
			 * set for this failed mailbox command.
			 */
			lpfc_nlp_put(ndlp);
			ndlp->nlp_flag &= ~NLP_REG_LOGIN_SEND;

			/* ELS rsp: Cannot issue reg_login for <NPortid> */
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				"0138 ELS rsp: Cannot issue reg_login for x%x "
				"Data: x%x x%x x%x\n",
				ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_state,
				ndlp->nlp_rpi);

			if (lpfc_nlp_not_used(ndlp)) {
				ndlp = NULL;
				/* Indicate node has already been released,
				 * should not reference to it from within
				 * the routine lpfc_els_free_iocb.
				 */
				cmdiocb->context1 = NULL;
			}
		} else {
			/* Do not drop node for lpfc_els_abort'ed ELS cmds */
			if (!lpfc_error_lost_link(irsp) &&
			    ndlp->nlp_flag & NLP_ACC_REGLOGIN) {
				if (lpfc_nlp_not_used(ndlp)) {
					ndlp = NULL;
					/* Indicate node has already been
					 * released, should not reference
					 * to it from within the routine
					 * lpfc_els_free_iocb.
					 */
					cmdiocb->context1 = NULL;
				}
			}
		}
		mp = (struct lpfc_dmabuf *)mbox->ctx_buf;
		if (mp) {
			lpfc_mbuf_free(phba, mp->virt, mp->phys);
			kfree(mp);
		}
		mempool_free(mbox, phba->mbox_mem_pool);
	}
out:
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag &= ~(NLP_ACC_REGLOGIN | NLP_RM_DFLT_RPI);
		spin_unlock_irq(shost->host_lock);

		/* If the node is not being used by another discovery thread,
		 * and we are sending a reject, we are done with it.
		 * Release driver reference count here and free associated
		 * resources.
		 */
		if (ls_rjt)
			if (lpfc_nlp_not_used(ndlp))
				/* Indicate node has already been released,
				 * should not reference to it from within
				 * the routine lpfc_els_free_iocb.
				 */
				cmdiocb->context1 = NULL;

	}

	lpfc_els_free_iocb(phba, cmdiocb);
	return;
}