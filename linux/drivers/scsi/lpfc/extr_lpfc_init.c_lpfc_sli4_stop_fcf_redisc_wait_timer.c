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
struct TYPE_2__ {int fcf_flag; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;

/* Variables and functions */
 int FCF_ACVL_DISC ; 
 int FCF_DEAD_DISC ; 
 int FCF_REDISC_PEND ; 
 int /*<<< orphan*/  __lpfc_sli4_stop_fcf_redisc_wait_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_stop_fcf_redisc_wait_timer(struct lpfc_hba *phba)
{
	spin_lock_irq(&phba->hbalock);
	if (!(phba->fcf.fcf_flag & FCF_REDISC_PEND)) {
		/* FCF rediscovery timer already fired or stopped */
		spin_unlock_irq(&phba->hbalock);
		return;
	}
	__lpfc_sli4_stop_fcf_redisc_wait_timer(phba);
	/* Clear failover in progress flags */
	phba->fcf.fcf_flag &= ~(FCF_DEAD_DISC | FCF_ACVL_DISC);
	spin_unlock_irq(&phba->hbalock);
}