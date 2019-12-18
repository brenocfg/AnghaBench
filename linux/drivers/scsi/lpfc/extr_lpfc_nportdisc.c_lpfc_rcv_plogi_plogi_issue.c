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
struct serv_parm {int /*<<< orphan*/  portName; } ;
struct TYPE_5__ {int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; } ;
struct TYPE_6__ {int /*<<< orphan*/  lsRjtError; TYPE_2__ b; } ;
struct ls_rjt {TYPE_3__ un; } ;
struct lpfc_vport {scalar_t__ num_disc_nodes; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; } ;
struct lpfc_name {int dummy; } ;
struct lpfc_iocbq {scalar_t__ context2; } ;
struct TYPE_4__ {int /*<<< orphan*/  elsLogiCol; } ;
struct lpfc_hba {TYPE_1__ fc_stat; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_NDISC_ACTIVE ; 
 int /*<<< orphan*/  LSEXP_CMD_IN_PROGRESS ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 int NLP_NPR_2B_DISC ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_end_rscn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_more_plogi (struct lpfc_vport*) ; 
 scalar_t__ lpfc_rcv_plogi (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ls_rjt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_plogi_plogi_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			   void *arg, uint32_t evt)
{
	struct Scsi_Host   *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_iocbq *cmdiocb = arg;
	struct lpfc_dmabuf *pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	uint32_t *lp = (uint32_t *) pcmd->virt;
	struct serv_parm *sp = (struct serv_parm *) (lp + 1);
	struct ls_rjt stat;
	int port_cmp;

	memset(&stat, 0, sizeof (struct ls_rjt));

	/* For a PLOGI, we only accept if our portname is less
	 * than the remote portname.
	 */
	phba->fc_stat.elsLogiCol++;
	port_cmp = memcmp(&vport->fc_portname, &sp->portName,
			  sizeof(struct lpfc_name));

	if (port_cmp >= 0) {
		/* Reject this request because the remote node will accept
		   ours */
		stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
		stat.un.b.lsRjtRsnCodeExp = LSEXP_CMD_IN_PROGRESS;
		lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp,
			NULL);
	} else {
		if (lpfc_rcv_plogi(vport, ndlp, cmdiocb) &&
		    (ndlp->nlp_flag & NLP_NPR_2B_DISC) &&
		    (vport->num_disc_nodes)) {
			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag &= ~NLP_NPR_2B_DISC;
			spin_unlock_irq(shost->host_lock);
			/* Check if there are more PLOGIs to be sent */
			lpfc_more_plogi(vport);
			if (vport->num_disc_nodes == 0) {
				spin_lock_irq(shost->host_lock);
				vport->fc_flag &= ~FC_NDISC_ACTIVE;
				spin_unlock_irq(shost->host_lock);
				lpfc_can_disctmo(vport);
				lpfc_end_rscn(vport);
			}
		}
	} /* If our portname was less */

	return ndlp->nlp_state;
}