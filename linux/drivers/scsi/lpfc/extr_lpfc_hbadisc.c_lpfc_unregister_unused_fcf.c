#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fcf_flag; } ;
struct lpfc_hba {int hba_flag; int /*<<< orphan*/  hbalock; TYPE_1__* pport; TYPE_2__ fcf; } ;
struct TYPE_3__ {scalar_t__ port_state; } ;

/* Variables and functions */
 int FCF_DISCOVERY ; 
 int FCF_REGISTERED ; 
 int HBA_FCOE_MODE ; 
 int HBA_FIP_SUPPORT ; 
 scalar_t__ LPFC_FLOGI ; 
 scalar_t__ lpfc_fcf_inuse (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unregister_fcf_rescan (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_unregister_unused_fcf(struct lpfc_hba *phba)
{
	/*
	 * If HBA is not running in FIP mode, if HBA does not support
	 * FCoE, if FCF discovery is ongoing, or if FCF has not been
	 * registered, do nothing.
	 */
	spin_lock_irq(&phba->hbalock);
	if (!(phba->hba_flag & HBA_FCOE_MODE) ||
	    !(phba->fcf.fcf_flag & FCF_REGISTERED) ||
	    !(phba->hba_flag & HBA_FIP_SUPPORT) ||
	    (phba->fcf.fcf_flag & FCF_DISCOVERY) ||
	    (phba->pport->port_state == LPFC_FLOGI)) {
		spin_unlock_irq(&phba->hbalock);
		return;
	}
	spin_unlock_irq(&phba->hbalock);

	if (lpfc_fcf_inuse(phba))
		return;

	lpfc_unregister_fcf_rescan(phba);
}