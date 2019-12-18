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
struct fsg_lun {scalar_t__ info_valid; scalar_t__ sense_data_info; void* unit_attention_data; void* sense_data; scalar_t__ prevent_medium_removal; } ;
struct fsg_dev {int dummy; } ;
struct fsg_common {scalar_t__ state; int fsg_num_buffers; unsigned int exception_req_tag; unsigned int ep0_req_tag; int /*<<< orphan*/  lock; int /*<<< orphan*/  cdev; TYPE_1__* fsg; struct fsg_lun** luns; struct fsg_dev* exception_arg; struct fsg_buffhd* buffhds; struct fsg_buffhd* next_buffhd_to_drain; struct fsg_buffhd* next_buffhd_to_fill; } ;
struct fsg_buffhd {scalar_t__ state; int /*<<< orphan*/  outreq; int /*<<< orphan*/  inreq; } ;
typedef  enum fsg_state { ____Placeholder_fsg_state } fsg_state ;
struct TYPE_2__ {int /*<<< orphan*/  bulk_in; int /*<<< orphan*/  atomic_bitflags; int /*<<< orphan*/  bulk_out; scalar_t__ bulk_out_enabled; scalar_t__ bulk_in_enabled; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fsg_lun**) ; 
 scalar_t__ BUF_STATE_EMPTY ; 
 scalar_t__ BUF_STATE_RECEIVING ; 
 scalar_t__ BUF_STATE_SENDING ; 
 int /*<<< orphan*/  DBG (struct fsg_common*,char*) ; 
#define  FSG_STATE_ABORT_BULK_OUT 133 
#define  FSG_STATE_CONFIG_CHANGE 132 
#define  FSG_STATE_EXIT 131 
#define  FSG_STATE_NORMAL 130 
#define  FSG_STATE_PROTOCOL_RESET 129 
#define  FSG_STATE_TERMINATED 128 
 int /*<<< orphan*/  IGNORE_BULK_OUT ; 
 int SIGUSR1 ; 
 void* SS_NO_SENSE ; 
 int /*<<< orphan*/  do_set_interface (struct fsg_common*,struct fsg_dev*) ; 
 int /*<<< orphan*/  ep0_queue (struct fsg_common*) ; 
 int /*<<< orphan*/  fsg_is_set (struct fsg_common*) ; 
 int kernel_dequeue_signal () ; 
 scalar_t__ likely (TYPE_1__*) ; 
 int /*<<< orphan*/  send_status (struct fsg_common*) ; 
 scalar_t__ sleep_thread (struct fsg_common*,int,struct fsg_buffhd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_composite_setup_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_clear_halt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_fifo_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_exception(struct fsg_common *common)
{
	int			i;
	struct fsg_buffhd	*bh;
	enum fsg_state		old_state;
	struct fsg_lun		*curlun;
	unsigned int		exception_req_tag;
	struct fsg_dev		*new_fsg;

	/*
	 * Clear the existing signals.  Anything but SIGUSR1 is converted
	 * into a high-priority EXIT exception.
	 */
	for (;;) {
		int sig = kernel_dequeue_signal();
		if (!sig)
			break;
		if (sig != SIGUSR1) {
			spin_lock_irq(&common->lock);
			if (common->state < FSG_STATE_EXIT)
				DBG(common, "Main thread exiting on signal\n");
			common->state = FSG_STATE_EXIT;
			spin_unlock_irq(&common->lock);
		}
	}

	/* Cancel all the pending transfers */
	if (likely(common->fsg)) {
		for (i = 0; i < common->fsg_num_buffers; ++i) {
			bh = &common->buffhds[i];
			if (bh->state == BUF_STATE_SENDING)
				usb_ep_dequeue(common->fsg->bulk_in, bh->inreq);
			if (bh->state == BUF_STATE_RECEIVING)
				usb_ep_dequeue(common->fsg->bulk_out,
					       bh->outreq);

			/* Wait for a transfer to become idle */
			if (sleep_thread(common, false, bh))
				return;
		}

		/* Clear out the controller's fifos */
		if (common->fsg->bulk_in_enabled)
			usb_ep_fifo_flush(common->fsg->bulk_in);
		if (common->fsg->bulk_out_enabled)
			usb_ep_fifo_flush(common->fsg->bulk_out);
	}

	/*
	 * Reset the I/O buffer states and pointers, the SCSI
	 * state, and the exception.  Then invoke the handler.
	 */
	spin_lock_irq(&common->lock);

	for (i = 0; i < common->fsg_num_buffers; ++i) {
		bh = &common->buffhds[i];
		bh->state = BUF_STATE_EMPTY;
	}
	common->next_buffhd_to_fill = &common->buffhds[0];
	common->next_buffhd_to_drain = &common->buffhds[0];
	exception_req_tag = common->exception_req_tag;
	new_fsg = common->exception_arg;
	old_state = common->state;
	common->state = FSG_STATE_NORMAL;

	if (old_state != FSG_STATE_ABORT_BULK_OUT) {
		for (i = 0; i < ARRAY_SIZE(common->luns); ++i) {
			curlun = common->luns[i];
			if (!curlun)
				continue;
			curlun->prevent_medium_removal = 0;
			curlun->sense_data = SS_NO_SENSE;
			curlun->unit_attention_data = SS_NO_SENSE;
			curlun->sense_data_info = 0;
			curlun->info_valid = 0;
		}
	}
	spin_unlock_irq(&common->lock);

	/* Carry out any extra actions required for the exception */
	switch (old_state) {
	case FSG_STATE_NORMAL:
		break;

	case FSG_STATE_ABORT_BULK_OUT:
		send_status(common);
		break;

	case FSG_STATE_PROTOCOL_RESET:
		/*
		 * In case we were forced against our will to halt a
		 * bulk endpoint, clear the halt now.  (The SuperH UDC
		 * requires this.)
		 */
		if (!fsg_is_set(common))
			break;
		if (test_and_clear_bit(IGNORE_BULK_OUT,
				       &common->fsg->atomic_bitflags))
			usb_ep_clear_halt(common->fsg->bulk_in);

		if (common->ep0_req_tag == exception_req_tag)
			ep0_queue(common);	/* Complete the status stage */

		/*
		 * Technically this should go here, but it would only be
		 * a waste of time.  Ditto for the INTERFACE_CHANGE and
		 * CONFIG_CHANGE cases.
		 */
		/* for (i = 0; i < common->ARRAY_SIZE(common->luns); ++i) */
		/*	if (common->luns[i]) */
		/*		common->luns[i]->unit_attention_data = */
		/*			SS_RESET_OCCURRED;  */
		break;

	case FSG_STATE_CONFIG_CHANGE:
		do_set_interface(common, new_fsg);
		if (new_fsg)
			usb_composite_setup_continue(common->cdev);
		break;

	case FSG_STATE_EXIT:
		do_set_interface(common, NULL);		/* Free resources */
		spin_lock_irq(&common->lock);
		common->state = FSG_STATE_TERMINATED;	/* Stop the thread */
		spin_unlock_irq(&common->lock);
		break;

	case FSG_STATE_TERMINATED:
		break;
	}
}