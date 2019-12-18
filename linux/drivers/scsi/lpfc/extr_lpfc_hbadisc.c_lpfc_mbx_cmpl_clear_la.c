#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {scalar_t__ port_type; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  port_state; } ;
struct lpfc_sli {int /*<<< orphan*/  sli_flag; TYPE_2__* sli3_ring; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HCregaddr; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  link_state; struct lpfc_sli sli; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_9__ {int mbxStatus; } ;
struct TYPE_7__ {TYPE_3__ mb; } ;
struct TYPE_10__ {TYPE_1__ u; struct lpfc_vport* vport; } ;
struct TYPE_8__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_3__ MAILBOX_t ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ABORT_DISCOVERY ; 
 int /*<<< orphan*/  HC_LAINT_ENA ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 size_t LPFC_EXTRA_RING ; 
 size_t LPFC_FCP_RING ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_HBA_READY ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  LPFC_PROCESS_LA ; 
 int /*<<< orphan*/  LPFC_STOP_IOCB_EVENT ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_clear_la(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport *vport = pmb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_sli   *psli = &phba->sli;
	MAILBOX_t *mb = &pmb->u.mb;
	uint32_t control;

	/* Since we don't do discovery right now, turn these off here */
	psli->sli3_ring[LPFC_EXTRA_RING].flag &= ~LPFC_STOP_IOCB_EVENT;
	psli->sli3_ring[LPFC_FCP_RING].flag &= ~LPFC_STOP_IOCB_EVENT;

	/* Check for error */
	if ((mb->mbxStatus) && (mb->mbxStatus != 0x1601)) {
		/* CLEAR_LA mbox error <mbxStatus> state <hba_state> */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
				 "0320 CLEAR_LA mbxStatus error x%x hba "
				 "state x%x\n",
				 mb->mbxStatus, vport->port_state);
		phba->link_state = LPFC_HBA_ERROR;
		goto out;
	}

	if (vport->port_type == LPFC_PHYSICAL_PORT)
		phba->link_state = LPFC_HBA_READY;

	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_PROCESS_LA;
	control = readl(phba->HCregaddr);
	control |= HC_LAINT_ENA;
	writel(control, phba->HCregaddr);
	readl(phba->HCregaddr); /* flush */
	spin_unlock_irq(&phba->hbalock);
	mempool_free(pmb, phba->mbox_mem_pool);
	return;

out:
	/* Device Discovery completes */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0225 Device Discovery completes\n");
	mempool_free(pmb, phba->mbox_mem_pool);

	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~FC_ABORT_DISCOVERY;
	spin_unlock_irq(shost->host_lock);

	lpfc_can_disctmo(vport);

	/* turn on Link Attention interrupts */

	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_PROCESS_LA;
	control = readl(phba->HCregaddr);
	control |= HC_LAINT_ENA;
	writel(control, phba->HCregaddr);
	readl(phba->HCregaddr); /* flush */
	spin_unlock_irq(&phba->hbalock);

	return;
}