#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  fc_flag; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  ctx_ndlp; struct lpfc_vport* vport; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_cmpl_reg_new_vport ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_reg_vpi (struct lpfc_vport*,TYPE_1__*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_register_new_vport(struct lpfc_hba *phba, struct lpfc_vport *vport,
			struct lpfc_nodelist *ndlp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	LPFC_MBOXQ_t *mbox;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (mbox) {
		lpfc_reg_vpi(vport, mbox);
		mbox->vport = vport;
		mbox->ctx_ndlp = lpfc_nlp_get(ndlp);
		mbox->mbox_cmpl = lpfc_cmpl_reg_new_vport;
		if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT)
		    == MBX_NOT_FINISHED) {
			/* mailbox command not success, decrement ndlp
			 * reference count for this command
			 */
			lpfc_nlp_put(ndlp);
			mempool_free(mbox, phba->mbox_mem_pool);

			lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
				"0253 Register VPI: Can't send mbox\n");
			goto mbox_err_exit;
		}
	} else {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
				 "0254 Register VPI: no memory\n");
		goto mbox_err_exit;
	}
	return;

mbox_err_exit:
	lpfc_vport_set_state(vport, FC_VPORT_FAILED);
	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~FC_VPORT_NEEDS_REG_VPI;
	spin_unlock_irq(shost->host_lock);
	return;
}