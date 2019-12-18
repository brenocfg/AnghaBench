#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  sli_flag; TYPE_4__* mbox_active; } ;
struct lpfc_hba {TYPE_3__ sli; int /*<<< orphan*/  hbalock; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_6__ {TYPE_1__ mb; } ;
struct TYPE_8__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  LPFC_BLOCK_MGMT_IO ; 
 int LPFC_MBOX_TMO ; 
 int LPFC_MBX_NO_WAIT ; 
 int /*<<< orphan*/  MBX_HEARTBEAT ; 
 int /*<<< orphan*/  jiffies ; 
 int lpfc_mbox_tmo_val (struct lpfc_hba*,TYPE_4__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
lpfc_block_mgmt_io(struct lpfc_hba *phba, int mbx_action)
{
	unsigned long iflag;
	uint8_t actcmd = MBX_HEARTBEAT;
	unsigned long timeout;

	spin_lock_irqsave(&phba->hbalock, iflag);
	phba->sli.sli_flag |= LPFC_BLOCK_MGMT_IO;
	spin_unlock_irqrestore(&phba->hbalock, iflag);
	if (mbx_action == LPFC_MBX_NO_WAIT)
		return;
	timeout = msecs_to_jiffies(LPFC_MBOX_TMO * 1000) + jiffies;
	spin_lock_irqsave(&phba->hbalock, iflag);
	if (phba->sli.mbox_active) {
		actcmd = phba->sli.mbox_active->u.mb.mbxCommand;
		/* Determine how long we might wait for the active mailbox
		 * command to be gracefully completed by firmware.
		 */
		timeout = msecs_to_jiffies(lpfc_mbox_tmo_val(phba,
				phba->sli.mbox_active) * 1000) + jiffies;
	}
	spin_unlock_irqrestore(&phba->hbalock, iflag);

	/* Wait for the outstnading mailbox command to complete */
	while (phba->sli.mbox_active) {
		/* Check active mailbox complete status every 2ms */
		msleep(2);
		if (time_after(jiffies, timeout)) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"2813 Mgmt IO is Blocked %x "
				"- mbox cmd %x still active\n",
				phba->sli.sli_flag, actcmd);
			break;
		}
	}
}