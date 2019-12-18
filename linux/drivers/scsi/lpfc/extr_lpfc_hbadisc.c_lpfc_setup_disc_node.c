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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int fc_flag; TYPE_1__* phba; } ;
struct lpfc_nodelist {int nlp_flag; scalar_t__ nlp_state; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {scalar_t__ nvmet_support; } ;

/* Variables and functions */
 int FC_NDISC_ACTIVE ; 
 int FC_RSCN_MODE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int NLP_NPR_2B_DISC ; 
 int NLP_RCV_PLOGI ; 
 scalar_t__ NLP_STE_ADISC_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 scalar_t__ NLP_STE_PLOGI_ISSUE ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lpfc_rscn_payload_check (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

struct lpfc_nodelist *
lpfc_setup_disc_node(struct lpfc_vport *vport, uint32_t did)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_nodelist *ndlp;

	ndlp = lpfc_findnode_did(vport, did);
	if (!ndlp) {
		if (vport->phba->nvmet_support)
			return NULL;
		if ((vport->fc_flag & FC_RSCN_MODE) != 0 &&
		    lpfc_rscn_payload_check(vport, did) == 0)
			return NULL;
		ndlp = lpfc_nlp_init(vport, did);
		if (!ndlp)
			return NULL;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
		return ndlp;
	} else if (!NLP_CHK_NODE_ACT(ndlp)) {
		if (vport->phba->nvmet_support)
			return NULL;
		ndlp = lpfc_enable_node(vport, ndlp, NLP_STE_NPR_NODE);
		if (!ndlp) {
			lpfc_printf_vlog(vport, KERN_WARNING, LOG_SLI,
					 "0014 Could not enable ndlp\n");
			return NULL;
		}
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
		return ndlp;
	}

	/* The NVME Target does not want to actively manage an rport.
	 * The goal is to allow the target to reset its state and clear
	 * pending IO in preparation for the initiator to recover.
	 */
	if ((vport->fc_flag & FC_RSCN_MODE) &&
	    !(vport->fc_flag & FC_NDISC_ACTIVE)) {
		if (lpfc_rscn_payload_check(vport, did)) {

			/* Since this node is marked for discovery,
			 * delay timeout is not needed.
			 */
			lpfc_cancel_retry_delay_tmo(vport, ndlp);

			/* NVME Target mode waits until rport is known to be
			 * impacted by the RSCN before it transitions.  No
			 * active management - just go to NPR provided the
			 * node had a valid login.
			 */
			if (vport->phba->nvmet_support)
				return ndlp;

			/* If we've already received a PLOGI from this NPort
			 * we don't need to try to discover it again.
			 */
			if (ndlp->nlp_flag & NLP_RCV_PLOGI)
				return NULL;

			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag |= NLP_NPR_2B_DISC;
			spin_unlock_irq(shost->host_lock);
		} else
			ndlp = NULL;
	} else {
		/* If the initiator received a PLOGI from this NPort or if the
		 * initiator is already in the process of discovery on it,
		 * there's no need to try to discover it again.
		 */
		if (ndlp->nlp_state == NLP_STE_ADISC_ISSUE ||
		    ndlp->nlp_state == NLP_STE_PLOGI_ISSUE ||
		    (!vport->phba->nvmet_support &&
		     ndlp->nlp_flag & NLP_RCV_PLOGI))
			return NULL;

		if (vport->phba->nvmet_support)
			return ndlp;

		/* Moving to NPR state clears unsolicited flags and
		 * allows for rediscovery
		 */
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);

		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
	}
	return ndlp;
}