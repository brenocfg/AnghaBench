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
struct skd_device {int state; int drive_state; int timer_countdown; int gendisk_on; int /*<<< orphan*/  waitq; int /*<<< orphan*/  start_queue; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIT_SR_DRIVE_FAULT ; 
 int FIT_SR_DRIVE_SOFT_RESET ; 
 int FIT_SR_DRIVE_STATE_MASK ; 
#define  SKD_DRVR_STATE_BUSY 144 
#define  SKD_DRVR_STATE_BUSY_ERASE 143 
#define  SKD_DRVR_STATE_BUSY_IMMINENT 142 
#define  SKD_DRVR_STATE_BUSY_SANITIZE 141 
#define  SKD_DRVR_STATE_DISAPPEARED 140 
#define  SKD_DRVR_STATE_FAULT 139 
#define  SKD_DRVR_STATE_IDLE 138 
#define  SKD_DRVR_STATE_LOAD 137 
#define  SKD_DRVR_STATE_ONLINE 136 
#define  SKD_DRVR_STATE_PAUSED 135 
#define  SKD_DRVR_STATE_PAUSING 134 
#define  SKD_DRVR_STATE_RESTARTING 133 
#define  SKD_DRVR_STATE_RESUMING 132 
#define  SKD_DRVR_STATE_STARTING 131 
#define  SKD_DRVR_STATE_STOPPING 130 
#define  SKD_DRVR_STATE_SYNCING 129 
#define  SKD_DRVR_STATE_WAIT_BOOT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_disable_interrupts (struct skd_device*) ; 
 int /*<<< orphan*/  skd_recover_requests (struct skd_device*) ; 
 int /*<<< orphan*/  skd_restart_device (struct skd_device*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skd_timer_tick_not_online(struct skd_device *skdev)
{
	switch (skdev->state) {
	case SKD_DRVR_STATE_IDLE:
	case SKD_DRVR_STATE_LOAD:
		break;
	case SKD_DRVR_STATE_BUSY_SANITIZE:
		dev_dbg(&skdev->pdev->dev,
			"drive busy sanitize[%x], driver[%x]\n",
			skdev->drive_state, skdev->state);
		/* If we've been in sanitize for 3 seconds, we figure we're not
		 * going to get anymore completions, so recover requests now
		 */
		if (skdev->timer_countdown > 0) {
			skdev->timer_countdown--;
			return;
		}
		skd_recover_requests(skdev);
		break;

	case SKD_DRVR_STATE_BUSY:
	case SKD_DRVR_STATE_BUSY_IMMINENT:
	case SKD_DRVR_STATE_BUSY_ERASE:
		dev_dbg(&skdev->pdev->dev, "busy[%x], countdown=%d\n",
			skdev->state, skdev->timer_countdown);
		if (skdev->timer_countdown > 0) {
			skdev->timer_countdown--;
			return;
		}
		dev_dbg(&skdev->pdev->dev,
			"busy[%x], timedout=%d, restarting device.",
			skdev->state, skdev->timer_countdown);
		skd_restart_device(skdev);
		break;

	case SKD_DRVR_STATE_WAIT_BOOT:
	case SKD_DRVR_STATE_STARTING:
		if (skdev->timer_countdown > 0) {
			skdev->timer_countdown--;
			return;
		}
		/* For now, we fault the drive.  Could attempt resets to
		 * revcover at some point. */
		skdev->state = SKD_DRVR_STATE_FAULT;

		dev_err(&skdev->pdev->dev, "DriveFault Connect Timeout (%x)\n",
			skdev->drive_state);

		/*start the queue so we can respond with error to requests */
		/* wakeup anyone waiting for startup complete */
		schedule_work(&skdev->start_queue);
		skdev->gendisk_on = -1;
		wake_up_interruptible(&skdev->waitq);
		break;

	case SKD_DRVR_STATE_ONLINE:
		/* shouldn't get here. */
		break;

	case SKD_DRVR_STATE_PAUSING:
	case SKD_DRVR_STATE_PAUSED:
		break;

	case SKD_DRVR_STATE_RESTARTING:
		if (skdev->timer_countdown > 0) {
			skdev->timer_countdown--;
			return;
		}
		/* For now, we fault the drive. Could attempt resets to
		 * revcover at some point. */
		skdev->state = SKD_DRVR_STATE_FAULT;
		dev_err(&skdev->pdev->dev,
			"DriveFault Reconnect Timeout (%x)\n",
			skdev->drive_state);

		/*
		 * Recovering does two things:
		 * 1. completes IO with error
		 * 2. reclaims dma resources
		 * When is it safe to recover requests?
		 * - if the drive state is faulted
		 * - if the state is still soft reset after out timeout
		 * - if the drive registers are dead (state = FF)
		 * If it is "unsafe", we still need to recover, so we will
		 * disable pci bus mastering and disable our interrupts.
		 */

		if ((skdev->drive_state == FIT_SR_DRIVE_SOFT_RESET) ||
		    (skdev->drive_state == FIT_SR_DRIVE_FAULT) ||
		    (skdev->drive_state == FIT_SR_DRIVE_STATE_MASK))
			/* It never came out of soft reset. Try to
			 * recover the requests and then let them
			 * fail. This is to mitigate hung processes. */
			skd_recover_requests(skdev);
		else {
			dev_err(&skdev->pdev->dev, "Disable BusMaster (%x)\n",
				skdev->drive_state);
			pci_disable_device(skdev->pdev);
			skd_disable_interrupts(skdev);
			skd_recover_requests(skdev);
		}

		/*start the queue so we can respond with error to requests */
		/* wakeup anyone waiting for startup complete */
		schedule_work(&skdev->start_queue);
		skdev->gendisk_on = -1;
		wake_up_interruptible(&skdev->waitq);
		break;

	case SKD_DRVR_STATE_RESUMING:
	case SKD_DRVR_STATE_STOPPING:
	case SKD_DRVR_STATE_SYNCING:
	case SKD_DRVR_STATE_FAULT:
	case SKD_DRVR_STATE_DISAPPEARED:
	default:
		break;
	}
}