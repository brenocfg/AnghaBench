#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_7__ {int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  cfg_link_speed; int /*<<< orphan*/  cfg_topology; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HCregaddr; TYPE_1__ sli; } ;
struct TYPE_8__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HC_LAINT_ENA ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 int /*<<< orphan*/  LPFC_PROCESS_LA ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 int MBX_BUSY ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  lpfc_init_link (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lpfc_link_reset(struct lpfc_vport *vport)
{
	struct lpfc_hba *phba = vport->phba;
	LPFC_MBOXQ_t *mbox;
	uint32_t control;
	int rc;

	lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
			 "2851 Attempt link reset\n");
	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
				"2852 Failed to allocate mbox memory");
		return 1;
	}

	/* Enable Link attention interrupts */
	if (phba->sli_rev <= LPFC_SLI_REV3) {
		spin_lock_irq(&phba->hbalock);
		phba->sli.sli_flag |= LPFC_PROCESS_LA;
		control = readl(phba->HCregaddr);
		control |= HC_LAINT_ENA;
		writel(control, phba->HCregaddr);
		readl(phba->HCregaddr); /* flush */
		spin_unlock_irq(&phba->hbalock);
	}

	lpfc_init_link(phba, mbox, phba->cfg_topology,
		       phba->cfg_link_speed);
	mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
	mbox->vport = vport;
	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if ((rc != MBX_BUSY) && (rc != MBX_SUCCESS)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
				"2853 Failed to issue INIT_LINK "
				"mbox command, rc:x%x\n", rc);
		mempool_free(mbox, phba->mbox_mem_pool);
		return 1;
	}

	return 0;
}