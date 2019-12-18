#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int fc_flag; scalar_t__ port_state; int /*<<< orphan*/  vpi_state; int /*<<< orphan*/  port_type; int /*<<< orphan*/  vpi; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; struct lpfc_vport* pport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_11__ {scalar_t__ upd; } ;
struct TYPE_12__ {TYPE_2__ varRegVpi; } ;
struct TYPE_13__ {int mbxStatus; TYPE_3__ un; } ;
struct TYPE_10__ {TYPE_4__ mb; } ;
struct TYPE_14__ {int /*<<< orphan*/  mbox_cmpl; struct lpfc_vport* vport; TYPE_1__ u; scalar_t__ ctx_ndlp; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_FABRIC ; 
 int FC_LOGO_RCVD_DID_CHNG ; 
 int FC_PUBLIC_LOOP ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 scalar_t__ LPFC_FDISC ; 
 int /*<<< orphan*/  LPFC_PHYSICAL_PORT ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  LPFC_VPI_REGISTERED ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_do_scr_ns_plogi (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_init_vpi (struct lpfc_hba*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_init_vpi_cmpl ; 
 int /*<<< orphan*/  lpfc_initial_fdisc (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_initial_flogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_fabric_reglogin (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_init_vfi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_mbx_unreg_vpi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli4_unreg_all_rpis (struct lpfc_vport*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_start_fdiscs (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_reg_new_vport(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport *vport = pmb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_nodelist *ndlp = (struct lpfc_nodelist *)pmb->ctx_ndlp;
	MAILBOX_t *mb = &pmb->u.mb;
	int rc;

	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~FC_VPORT_NEEDS_REG_VPI;
	spin_unlock_irq(shost->host_lock);

	if (mb->mbxStatus) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
				"0915 Register VPI failed : Status: x%x"
				" upd bit: x%x \n", mb->mbxStatus,
				 mb->un.varRegVpi.upd);
		if (phba->sli_rev == LPFC_SLI_REV4 &&
			mb->un.varRegVpi.upd)
			goto mbox_err_exit ;

		switch (mb->mbxStatus) {
		case 0x11:	/* unsupported feature */
		case 0x9603:	/* max_vpi exceeded */
		case 0x9602:	/* Link event since CLEAR_LA */
			/* giving up on vport registration */
			lpfc_vport_set_state(vport, FC_VPORT_FAILED);
			spin_lock_irq(shost->host_lock);
			vport->fc_flag &= ~(FC_FABRIC | FC_PUBLIC_LOOP);
			spin_unlock_irq(shost->host_lock);
			lpfc_can_disctmo(vport);
			break;
		/* If reg_vpi fail with invalid VPI status, re-init VPI */
		case 0x20:
			spin_lock_irq(shost->host_lock);
			vport->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
			spin_unlock_irq(shost->host_lock);
			lpfc_init_vpi(phba, pmb, vport->vpi);
			pmb->vport = vport;
			pmb->mbox_cmpl = lpfc_init_vpi_cmpl;
			rc = lpfc_sli_issue_mbox(phba, pmb,
				MBX_NOWAIT);
			if (rc == MBX_NOT_FINISHED) {
				lpfc_printf_vlog(vport,
					KERN_ERR, LOG_MBOX,
					"2732 Failed to issue INIT_VPI"
					" mailbox command\n");
			} else {
				lpfc_nlp_put(ndlp);
				return;
			}
			/* fall through */
		default:
			/* Try to recover from this error */
			if (phba->sli_rev == LPFC_SLI_REV4)
				lpfc_sli4_unreg_all_rpis(vport);
			lpfc_mbx_unreg_vpi(vport);
			spin_lock_irq(shost->host_lock);
			vport->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
			spin_unlock_irq(shost->host_lock);
			if (mb->mbxStatus == MBX_NOT_FINISHED)
				break;
			if ((vport->port_type == LPFC_PHYSICAL_PORT) &&
			    !(vport->fc_flag & FC_LOGO_RCVD_DID_CHNG)) {
				if (phba->sli_rev == LPFC_SLI_REV4)
					lpfc_issue_init_vfi(vport);
				else
					lpfc_initial_flogi(vport);
			} else {
				lpfc_initial_fdisc(vport);
			}
			break;
		}
	} else {
		spin_lock_irq(shost->host_lock);
		vport->vpi_state |= LPFC_VPI_REGISTERED;
		spin_unlock_irq(shost->host_lock);
		if (vport == phba->pport) {
			if (phba->sli_rev < LPFC_SLI_REV4)
				lpfc_issue_fabric_reglogin(vport);
			else {
				/*
				 * If the physical port is instantiated using
				 * FDISC, do not start vport discovery.
				 */
				if (vport->port_state != LPFC_FDISC)
					lpfc_start_fdiscs(phba);
				lpfc_do_scr_ns_plogi(phba, vport);
			}
		} else
			lpfc_do_scr_ns_plogi(phba, vport);
	}
mbox_err_exit:
	/* Now, we decrement the ndlp reference count held for this
	 * callback function
	 */
	lpfc_nlp_put(ndlp);

	mempool_free(pmb, phba->mbox_mem_pool);
	return;
}