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
struct cs_hsi_iface {TYPE_1__* cl; int /*<<< orphan*/  lock; int /*<<< orphan*/  datawait; int /*<<< orphan*/  data_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int CS_HSI_TRANSFER_TIMEOUT_MS ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  cs_state_xfer_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int schedule_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int cs_hsi_data_sync(struct cs_hsi_iface *hi)
{
	int r = 0;

	spin_lock_bh(&hi->lock);

	if (!cs_state_xfer_active(hi->data_state)) {
		dev_dbg(&hi->cl->device, "hsi_data_sync break, idle\n");
		goto out;
	}

	for (;;) {
		int s;
		DEFINE_WAIT(wait);
		if (!cs_state_xfer_active(hi->data_state))
			goto out;
		if (signal_pending(current)) {
			r = -ERESTARTSYS;
			goto out;
		}
		/**
		 * prepare_to_wait must be called with hi->lock held
		 * so that callbacks can check for waitqueue_active()
		 */
		prepare_to_wait(&hi->datawait, &wait, TASK_INTERRUPTIBLE);
		spin_unlock_bh(&hi->lock);
		s = schedule_timeout(
			msecs_to_jiffies(CS_HSI_TRANSFER_TIMEOUT_MS));
		spin_lock_bh(&hi->lock);
		finish_wait(&hi->datawait, &wait);
		if (!s) {
			dev_dbg(&hi->cl->device,
				"hsi_data_sync timeout after %d ms\n",
				CS_HSI_TRANSFER_TIMEOUT_MS);
			r = -EIO;
			goto out;
		}
	}

out:
	spin_unlock_bh(&hi->lock);
	dev_dbg(&hi->cl->device, "hsi_data_sync done with res %d\n", r);

	return r;
}