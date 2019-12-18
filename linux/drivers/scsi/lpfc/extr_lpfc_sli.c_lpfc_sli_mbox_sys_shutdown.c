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
struct lpfc_sli {int sli_flag; scalar_t__ mbox_active; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; struct lpfc_sli sli; } ;

/* Variables and functions */
 int LPFC_MBOX_TMO ; 
 int LPFC_MBX_NO_WAIT ; 
 int LPFC_SLI_ACTIVE ; 
 int LPFC_SLI_ASYNC_MBX_BLK ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int lpfc_mbox_tmo_val (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli_mbox_sys_flush (struct lpfc_hba*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,unsigned long) ; 

void
lpfc_sli_mbox_sys_shutdown(struct lpfc_hba *phba, int mbx_action)
{
	struct lpfc_sli *psli = &phba->sli;
	unsigned long timeout;

	if (mbx_action == LPFC_MBX_NO_WAIT) {
		/* delay 100ms for port state */
		msleep(100);
		lpfc_sli_mbox_sys_flush(phba);
		return;
	}
	timeout = msecs_to_jiffies(LPFC_MBOX_TMO * 1000) + jiffies;

	/* Disable softirqs, including timers from obtaining phba->hbalock */
	local_bh_disable();

	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_SLI_ASYNC_MBX_BLK;

	if (psli->sli_flag & LPFC_SLI_ACTIVE) {
		/* Determine how long we might wait for the active mailbox
		 * command to be gracefully completed by firmware.
		 */
		if (phba->sli.mbox_active)
			timeout = msecs_to_jiffies(lpfc_mbox_tmo_val(phba,
						phba->sli.mbox_active) *
						1000) + jiffies;
		spin_unlock_irq(&phba->hbalock);

		/* Enable softirqs again, done with phba->hbalock */
		local_bh_enable();

		while (phba->sli.mbox_active) {
			/* Check active mailbox complete status every 2ms */
			msleep(2);
			if (time_after(jiffies, timeout))
				/* Timeout, let the mailbox flush routine to
				 * forcefully release active mailbox command
				 */
				break;
		}
	} else {
		spin_unlock_irq(&phba->hbalock);

		/* Enable softirqs again, done with phba->hbalock */
		local_bh_enable();
	}

	lpfc_sli_mbox_sys_flush(phba);
}