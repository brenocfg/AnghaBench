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
struct TYPE_2__ {int /*<<< orphan*/  fcf_flag; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_REGISTERED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int lpfc_sli4_unregister_fcf (struct lpfc_hba*) ; 
 int lpfc_unregister_fcf_prep (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_unregister_fcf(struct lpfc_hba *phba)
{
	int rc;

	/* Preparation for unregistering fcf */
	rc = lpfc_unregister_fcf_prep(phba);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY,
				"2749 Failed to prepare for unregistering "
				"HBA's FCF record: rc=%d\n", rc);
		return;
	}

	/* Now, unregister FCF record and reset HBA FCF state */
	rc = lpfc_sli4_unregister_fcf(phba);
	if (rc)
		return;
	/* Set proper HBA FCF states after successful unregister FCF */
	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag &= ~FCF_REGISTERED;
	spin_unlock_irq(&phba->hbalock);
}