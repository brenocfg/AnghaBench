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
struct TYPE_3__ {int /*<<< orphan*/  ctl_src_addr; } ;
struct fnic {scalar_t__ state; int /*<<< orphan*/  fnic_lock; TYPE_2__* lport; int /*<<< orphan*/ * remove_wait; TYPE_1__ ctlr; } ;
struct fc_lport {int dummy; } ;
typedef  enum fnic_state { ____Placeholder_fnic_state } fnic_state ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ FNIC_IN_ETH_MODE ; 
 scalar_t__ FNIC_IN_FC_TRANS_ETH_MODE ; 
 int FNIC_RMDEVICE_TIMEOUT ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int fnic_fw_reset_handler (struct fnic*) ; 
 int /*<<< orphan*/  fnic_update_mac_locked (struct fnic*,int /*<<< orphan*/ ) ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  remove_wait ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fnic_scsi_abort_io(struct fc_lport *lp)
{
	int err = 0;
	unsigned long flags;
	enum fnic_state old_state;
	struct fnic *fnic = lport_priv(lp);
	DECLARE_COMPLETION_ONSTACK(remove_wait);

	/* Issue firmware reset for fnic, wait for reset to complete */
retry_fw_reset:
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	if (unlikely(fnic->state == FNIC_IN_FC_TRANS_ETH_MODE)) {
		/* fw reset is in progress, poll for its completion */
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		schedule_timeout(msecs_to_jiffies(100));
		goto retry_fw_reset;
	}

	fnic->remove_wait = &remove_wait;
	old_state = fnic->state;
	fnic->state = FNIC_IN_FC_TRANS_ETH_MODE;
	fnic_update_mac_locked(fnic, fnic->ctlr.ctl_src_addr);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	err = fnic_fw_reset_handler(fnic);
	if (err) {
		spin_lock_irqsave(&fnic->fnic_lock, flags);
		if (fnic->state == FNIC_IN_FC_TRANS_ETH_MODE)
			fnic->state = old_state;
		fnic->remove_wait = NULL;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		return;
	}

	/* Wait for firmware reset to complete */
	wait_for_completion_timeout(&remove_wait,
				    msecs_to_jiffies(FNIC_RMDEVICE_TIMEOUT));

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->remove_wait = NULL;
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_scsi_abort_io %s\n",
		      (fnic->state == FNIC_IN_ETH_MODE) ?
		      "SUCCESS" : "FAILED");
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

}