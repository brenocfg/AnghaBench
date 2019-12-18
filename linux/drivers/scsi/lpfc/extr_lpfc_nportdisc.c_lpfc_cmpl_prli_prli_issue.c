#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {scalar_t__ port_type; scalar_t__ cfg_restrict_login; struct lpfc_hba* phba; } ;
struct lpfc_nvme_prli {int /*<<< orphan*/  word5; int /*<<< orphan*/  word4; int /*<<< orphan*/  word1; } ;
struct lpfc_nodelist {int nlp_type; int nvme_fb_size; scalar_t__ fc4_prli_sent; int /*<<< orphan*/  nlp_state; scalar_t__ nlp_DID; void* nlp_prev_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_fcp_info; int /*<<< orphan*/  nlp_nvme_info; int /*<<< orphan*/  nlp_fc4_type; } ;
struct TYPE_6__ {scalar_t__ ulpStatus; } ;
struct TYPE_4__ {struct lpfc_iocbq* rsp_iocb; } ;
struct lpfc_iocbq {int iocb_flag; TYPE_3__ iocb; TYPE_1__ context_un; } ;
struct lpfc_hba {int /*<<< orphan*/  nvmet_support; scalar_t__ cfg_nvme_enable_fb; scalar_t__ nsler; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {scalar_t__ acceptRspCode; scalar_t__ prliType; scalar_t__ targetFunc; scalar_t__ Retry; scalar_t__ writeXferRdyDis; scalar_t__ initiatorFunc; } ;
typedef  TYPE_2__ PRLI ;
typedef  TYPE_3__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LOG_NVME_DISC ; 
 scalar_t__ LPFC_NPIV_PORT ; 
 int LPFC_NVME_FB_SHIFT ; 
 int LPFC_NVME_MAX_FB ; 
 int LPFC_PRLI_FCP_REQ ; 
 int LPFC_PRLI_NVME_REQ ; 
 int /*<<< orphan*/  NLP_FC4_FCP ; 
 int /*<<< orphan*/  NLP_FC4_NVME ; 
 int /*<<< orphan*/  NLP_FCP_2_DEVICE ; 
 int NLP_FCP_INITIATOR ; 
 int NLP_FCP_TARGET ; 
 int /*<<< orphan*/  NLP_FIRSTBURST ; 
 int NLP_NVME_DISCOVERY ; 
 int NLP_NVME_INITIATOR ; 
 int /*<<< orphan*/  NLP_NVME_NSLER ; 
 int NLP_NVME_TARGET ; 
 int /*<<< orphan*/  NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 void* NLP_STE_PRLI_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  NLP_TARGET_REMOVE ; 
 scalar_t__ PRLI_FCP_TYPE ; 
 int PRLI_NVME_TYPE ; 
 scalar_t__ PRLI_REQ_EXECUTED ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int bf_get_be32 (int /*<<< orphan*/ ,struct lpfc_nvme_prli*) ; 
 void* lpfc_check_elscmpl_iocb (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_issue_els_logo (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  prli_acc_rsp_code ; 
 int /*<<< orphan*/  prli_disc ; 
 int /*<<< orphan*/  prli_fb_sz ; 
 int /*<<< orphan*/  prli_fba ; 
 int /*<<< orphan*/  prli_init ; 
 int /*<<< orphan*/  prli_nsler ; 
 int /*<<< orphan*/  prli_tgt ; 
 int /*<<< orphan*/  prli_type_code ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_cmpl_prli_prli_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_iocbq *cmdiocb, *rspiocb;
	struct lpfc_hba   *phba = vport->phba;
	IOCB_t *irsp;
	PRLI *npr;
	struct lpfc_nvme_prli *nvpr;
	void *temp_ptr;

	cmdiocb = (struct lpfc_iocbq *) arg;
	rspiocb = cmdiocb->context_un.rsp_iocb;

	/* A solicited PRLI is either FCP or NVME.  The PRLI cmd/rsp
	 * format is different so NULL the two PRLI types so that the
	 * driver correctly gets the correct context.
	 */
	npr = NULL;
	nvpr = NULL;
	temp_ptr = lpfc_check_elscmpl_iocb(phba, cmdiocb, rspiocb);
	if (cmdiocb->iocb_flag & LPFC_PRLI_FCP_REQ)
		npr = (PRLI *) temp_ptr;
	else if (cmdiocb->iocb_flag & LPFC_PRLI_NVME_REQ)
		nvpr = (struct lpfc_nvme_prli *) temp_ptr;

	irsp = &rspiocb->iocb;
	if (irsp->ulpStatus) {
		if ((vport->port_type == LPFC_NPIV_PORT) &&
		    vport->cfg_restrict_login) {
			goto out;
		}

		/* Adjust the nlp_type accordingly if the PRLI failed */
		if (npr)
			ndlp->nlp_fc4_type &= ~NLP_FC4_FCP;
		if (nvpr)
			ndlp->nlp_fc4_type &= ~NLP_FC4_NVME;

		/* We can't set the DSM state till BOTH PRLIs complete */
		goto out_err;
	}

	if (npr && (npr->acceptRspCode == PRLI_REQ_EXECUTED) &&
	    (npr->prliType == PRLI_FCP_TYPE)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_DISC,
				 "6028 FCP NPR PRLI Cmpl Init %d Target %d\n",
				 npr->initiatorFunc,
				 npr->targetFunc);
		if (npr->initiatorFunc)
			ndlp->nlp_type |= NLP_FCP_INITIATOR;
		if (npr->targetFunc) {
			ndlp->nlp_type |= NLP_FCP_TARGET;
			if (npr->writeXferRdyDis)
				ndlp->nlp_flag |= NLP_FIRSTBURST;
		}
		if (npr->Retry)
			ndlp->nlp_fcp_info |= NLP_FCP_2_DEVICE;

	} else if (nvpr &&
		   (bf_get_be32(prli_acc_rsp_code, nvpr) ==
		    PRLI_REQ_EXECUTED) &&
		   (bf_get_be32(prli_type_code, nvpr) ==
		    PRLI_NVME_TYPE)) {

		/* Complete setting up the remote ndlp personality. */
		if (bf_get_be32(prli_init, nvpr))
			ndlp->nlp_type |= NLP_NVME_INITIATOR;

		if (phba->nsler && bf_get_be32(prli_nsler, nvpr))
			ndlp->nlp_nvme_info |= NLP_NVME_NSLER;
		else
			ndlp->nlp_nvme_info &= ~NLP_NVME_NSLER;

		/* Target driver cannot solicit NVME FB. */
		if (bf_get_be32(prli_tgt, nvpr)) {
			/* Complete the nvme target roles.  The transport
			 * needs to know if the rport is capable of
			 * discovery in addition to its role.
			 */
			ndlp->nlp_type |= NLP_NVME_TARGET;
			if (bf_get_be32(prli_disc, nvpr))
				ndlp->nlp_type |= NLP_NVME_DISCOVERY;

			/*
			 * If prli_fba is set, the Target supports FirstBurst.
			 * If prli_fb_sz is 0, the FirstBurst size is unlimited,
			 * otherwise it defines the actual size supported by
			 * the NVME Target.
			 */
			if ((bf_get_be32(prli_fba, nvpr) == 1) &&
			    (phba->cfg_nvme_enable_fb) &&
			    (!phba->nvmet_support)) {
				/* Both sides support FB. The target's first
				 * burst size is a 512 byte encoded value.
				 */
				ndlp->nlp_flag |= NLP_FIRSTBURST;
				ndlp->nvme_fb_size = bf_get_be32(prli_fb_sz,
								 nvpr);

				/* Expressed in units of 512 bytes */
				if (ndlp->nvme_fb_size)
					ndlp->nvme_fb_size <<=
						LPFC_NVME_FB_SHIFT;
				else
					ndlp->nvme_fb_size = LPFC_NVME_MAX_FB;
			}
		}

		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME_DISC,
				 "6029 NVME PRLI Cmpl w1 x%08x "
				 "w4 x%08x w5 x%08x flag x%x, "
				 "fcp_info x%x nlp_type x%x\n",
				 be32_to_cpu(nvpr->word1),
				 be32_to_cpu(nvpr->word4),
				 be32_to_cpu(nvpr->word5),
				 ndlp->nlp_flag, ndlp->nlp_fcp_info,
				 ndlp->nlp_type);
	}
	if (!(ndlp->nlp_type & NLP_FCP_TARGET) &&
	    (vport->port_type == LPFC_NPIV_PORT) &&
	     vport->cfg_restrict_login) {
out:
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_TARGET_REMOVE;
		spin_unlock_irq(shost->host_lock);
		lpfc_issue_els_logo(vport, ndlp, 0);

		ndlp->nlp_prev_state = NLP_STE_PRLI_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		return ndlp->nlp_state;
	}

out_err:
	/* The ndlp state cannot move to MAPPED or UNMAPPED before all PRLIs
	 * are complete.
	 */
	if (ndlp->fc4_prli_sent == 0) {
		ndlp->nlp_prev_state = NLP_STE_PRLI_ISSUE;
		if (ndlp->nlp_type & (NLP_FCP_TARGET | NLP_NVME_TARGET))
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_MAPPED_NODE);
		else if (ndlp->nlp_type &
			 (NLP_FCP_INITIATOR | NLP_NVME_INITIATOR))
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNMAPPED_NODE);
	} else
		lpfc_printf_vlog(vport,
				 KERN_INFO, LOG_ELS,
				 "3067 PRLI's still outstanding "
				 "on x%06x - count %d, Pend Node Mode "
				 "transition...\n",
				 ndlp->nlp_DID, ndlp->fc4_prli_sent);

	return ndlp->nlp_state;
}