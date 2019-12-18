#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_MBX_NO_WAIT ; 
 int /*<<< orphan*/  lpfc_hba_down_post (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_flush_io_rings (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_offline_eratt(struct lpfc_hba *phba)
{
	spin_lock_irq(&phba->hbalock);
	phba->link_state = LPFC_HBA_ERROR;
	spin_unlock_irq(&phba->hbalock);

	lpfc_offline_prep(phba, LPFC_MBX_NO_WAIT);
	lpfc_sli_flush_io_rings(phba);
	lpfc_offline(phba);
	lpfc_hba_down_post(phba);
	lpfc_unblock_mgmt_io(phba);
}