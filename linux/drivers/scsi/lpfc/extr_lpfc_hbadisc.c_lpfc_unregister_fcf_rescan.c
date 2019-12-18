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
struct TYPE_4__ {scalar_t__ flag; } ;
struct TYPE_5__ {int /*<<< orphan*/  fcf_flag; TYPE_1__ current_rec; } ;
struct lpfc_hba {scalar_t__ link_state; TYPE_3__* pport; int /*<<< orphan*/  hbalock; TYPE_2__ fcf; } ;
struct TYPE_6__ {int load_flag; int port_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_INIT_DISC ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_DISCOVERY ; 
 int LOG_MBOX ; 
 int /*<<< orphan*/  LPFC_FCOE_FCF_GET_FIRST ; 
 scalar_t__ LPFC_LINK_UP ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli4_clear_fcf_rr_bmask (struct lpfc_hba*) ; 
 int lpfc_sli4_fcf_scan_read_fcf_rec (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_sli4_unregister_fcf (struct lpfc_hba*) ; 
 int lpfc_unregister_fcf_prep (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_unregister_fcf_rescan(struct lpfc_hba *phba)
{
	int rc;

	/* Preparation for unregistering fcf */
	rc = lpfc_unregister_fcf_prep(phba);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY,
				"2748 Failed to prepare for unregistering "
				"HBA's FCF record: rc=%d\n", rc);
		return;
	}

	/* Now, unregister FCF record and reset HBA FCF state */
	rc = lpfc_sli4_unregister_fcf(phba);
	if (rc)
		return;
	/* Reset HBA FCF states after successful unregister FCF */
	phba->fcf.fcf_flag = 0;
	phba->fcf.current_rec.flag = 0;

	/*
	 * If driver is not unloading, check if there is any other
	 * FCF record that can be used for discovery.
	 */
	if ((phba->pport->load_flag & FC_UNLOADING) ||
	    (phba->link_state < LPFC_LINK_UP))
		return;

	/* This is considered as the initial FCF discovery scan */
	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag |= FCF_INIT_DISC;
	spin_unlock_irq(&phba->hbalock);

	/* Reset FCF roundrobin bmask for new discovery */
	lpfc_sli4_clear_fcf_rr_bmask(phba);

	rc = lpfc_sli4_fcf_scan_read_fcf_rec(phba, LPFC_FCOE_FCF_GET_FIRST);

	if (rc) {
		spin_lock_irq(&phba->hbalock);
		phba->fcf.fcf_flag &= ~FCF_INIT_DISC;
		spin_unlock_irq(&phba->hbalock);
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY|LOG_MBOX,
				"2553 lpfc_unregister_unused_fcf failed "
				"to read FCF record HBA state x%x\n",
				phba->pport->port_state);
	}
}