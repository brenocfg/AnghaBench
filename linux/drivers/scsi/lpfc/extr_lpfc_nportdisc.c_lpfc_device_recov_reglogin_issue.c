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
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  nvmet_support; } ;

/* Variables and functions */
 int FC_RSCN_DEFERRED ; 
 int NLP_IGNR_REG_CMPL ; 
 int NLP_NODEV_REMOVE ; 
 int NLP_NPR_2B_DISC ; 
 int NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_REG_LOGIN_ISSUE ; 
 int /*<<< orphan*/  lpfc_disc_set_adisc (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_device_recov_reglogin_issue(struct lpfc_vport *vport,
				 struct lpfc_nodelist *ndlp,
				 void *arg,
				 uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	/* Don't do anything that will mess up processing of the
	 * previous RSCN.
	 */
	if (vport->fc_flag & FC_RSCN_DEFERRED)
		return ndlp->nlp_state;

	ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	spin_lock_irq(shost->host_lock);

	/* If we are a target we won't immediately transition into PRLI,
	 * so if REG_LOGIN already completed we don't need to ignore it.
	 */
	if (!(ndlp->nlp_flag & NLP_RPI_REGISTERED) ||
	    !vport->phba->nvmet_support)
		ndlp->nlp_flag |= NLP_IGNR_REG_CMPL;

	ndlp->nlp_flag &= ~(NLP_NODEV_REMOVE | NLP_NPR_2B_DISC);
	spin_unlock_irq(shost->host_lock);
	lpfc_disc_set_adisc(vport, ndlp);
	return ndlp->nlp_state;
}