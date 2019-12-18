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
struct us_data {int fflags; scalar_t__ max_lun; int /*<<< orphan*/  dev_mutex; struct scsi_cmnd* srb; int /*<<< orphan*/  dflags; int /*<<< orphan*/  notify; int /*<<< orphan*/  pusb_dev; int /*<<< orphan*/  (* proto_handler ) (struct scsi_cmnd*,struct us_data*) ;int /*<<< orphan*/  cmnd_ready; } ;
struct scsi_cmnd {int result; scalar_t__ sc_data_direction; scalar_t__* cmnd; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ lun; scalar_t__ id; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 scalar_t__ DMA_BIDIRECTIONAL ; 
 scalar_t__ INQUIRY ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  US_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  US_FLIDX_ABORTING ; 
 int /*<<< orphan*/  US_FLIDX_TIMED_OUT ; 
 int US_FL_FIX_INQUIRY ; 
 int US_FL_SCM_MULT_TARG ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_inquiry_response (struct us_data*,unsigned char*,int) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  scsi_lock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unlock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*,struct us_data*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 
 int /*<<< orphan*/  usb_stor_show_command (struct us_data*,struct scsi_cmnd*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_stor_control_thread(void * __us)
{
	struct us_data *us = (struct us_data *)__us;
	struct Scsi_Host *host = us_to_host(us);
	struct scsi_cmnd *srb;

	for (;;) {
		usb_stor_dbg(us, "*** thread sleeping\n");
		if (wait_for_completion_interruptible(&us->cmnd_ready))
			break;

		usb_stor_dbg(us, "*** thread awakened\n");

		/* lock the device pointers */
		mutex_lock(&(us->dev_mutex));

		/* lock access to the state */
		scsi_lock(host);

		/* When we are called with no command pending, we're done */
		srb = us->srb;
		if (srb == NULL) {
			scsi_unlock(host);
			mutex_unlock(&us->dev_mutex);
			usb_stor_dbg(us, "-- exiting\n");
			break;
		}

		/* has the command timed out *already* ? */
		if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
			srb->result = DID_ABORT << 16;
			goto SkipForAbort;
		}

		scsi_unlock(host);

		/*
		 * reject the command if the direction indicator
		 * is UNKNOWN
		 */
		if (srb->sc_data_direction == DMA_BIDIRECTIONAL) {
			usb_stor_dbg(us, "UNKNOWN data direction\n");
			srb->result = DID_ERROR << 16;
		}

		/*
		 * reject if target != 0 or if LUN is higher than
		 * the maximum known LUN
		 */
		else if (srb->device->id &&
				!(us->fflags & US_FL_SCM_MULT_TARG)) {
			usb_stor_dbg(us, "Bad target number (%d:%llu)\n",
				     srb->device->id,
				     srb->device->lun);
			srb->result = DID_BAD_TARGET << 16;
		}

		else if (srb->device->lun > us->max_lun) {
			usb_stor_dbg(us, "Bad LUN (%d:%llu)\n",
				     srb->device->id,
				     srb->device->lun);
			srb->result = DID_BAD_TARGET << 16;
		}

		/*
		 * Handle those devices which need us to fake
		 * their inquiry data
		 */
		else if ((srb->cmnd[0] == INQUIRY) &&
			    (us->fflags & US_FL_FIX_INQUIRY)) {
			unsigned char data_ptr[36] = {
			    0x00, 0x80, 0x02, 0x02,
			    0x1F, 0x00, 0x00, 0x00};

			usb_stor_dbg(us, "Faking INQUIRY command\n");
			fill_inquiry_response(us, data_ptr, 36);
			srb->result = SAM_STAT_GOOD;
		}

		/* we've got a command, let's do it! */
		else {
			US_DEBUG(usb_stor_show_command(us, srb));
			us->proto_handler(srb, us);
			usb_mark_last_busy(us->pusb_dev);
		}

		/* lock access to the state */
		scsi_lock(host);

		/* was the command aborted? */
		if (srb->result == DID_ABORT << 16) {
SkipForAbort:
			usb_stor_dbg(us, "scsi command aborted\n");
			srb = NULL;	/* Don't call srb->scsi_done() */
		}

		/*
		 * If an abort request was received we need to signal that
		 * the abort has finished.  The proper test for this is
		 * the TIMED_OUT flag, not srb->result == DID_ABORT, because
		 * the timeout might have occurred after the command had
		 * already completed with a different result code.
		 */
		if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
			complete(&(us->notify));

			/* Allow USB transfers to resume */
			clear_bit(US_FLIDX_ABORTING, &us->dflags);
			clear_bit(US_FLIDX_TIMED_OUT, &us->dflags);
		}

		/* finished working on this command */
		us->srb = NULL;
		scsi_unlock(host);

		/* unlock the device pointers */
		mutex_unlock(&us->dev_mutex);

		/* now that the locks are released, notify the SCSI core */
		if (srb) {
			usb_stor_dbg(us, "scsi cmd done, result=0x%x\n",
					srb->result);
			srb->scsi_done(srb);
		}
	} /* for (;;) */

	/* Wait until we are told to stop */
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (kthread_should_stop())
			break;
		schedule();
	}
	__set_current_state(TASK_RUNNING);
	return 0;
}