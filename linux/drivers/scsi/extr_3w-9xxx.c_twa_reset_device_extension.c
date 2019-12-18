#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct TYPE_9__ {scalar_t__* state; int* free_queue; int /*<<< orphan*/  chrdev_request_id; int /*<<< orphan*/  flags; TYPE_1__* host; scalar_t__ reset_print; void* pending_tail; void* pending_head; scalar_t__ pending_request_count; scalar_t__ posted_request_count; void* free_tail; void* free_head; struct scsi_cmnd** srb; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_2__ TW_Device_Extension ;

/* Variables and functions */
 int DID_RESET ; 
 int /*<<< orphan*/  TW_DISABLE_INTERRUPTS (TYPE_2__*) ; 
 int /*<<< orphan*/  TW_ENABLE_AND_CLEAR_INTERRUPTS (TYPE_2__*) ; 
 int /*<<< orphan*/  TW_IN_RESET ; 
 int /*<<< orphan*/  TW_IOCTL_CHRDEV_FREE ; 
 int /*<<< orphan*/  TW_MASK_COMMAND_INTERRUPT (TYPE_2__*) ; 
 int TW_Q_LENGTH ; 
 void* TW_Q_START ; 
 scalar_t__ TW_S_COMPLETED ; 
 scalar_t__ TW_S_FINISHED ; 
 scalar_t__ TW_S_INITIAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ twa_command_mapped (struct scsi_cmnd*) ; 
 scalar_t__ twa_reset_sequence (TYPE_2__*,int) ; 

__attribute__((used)) static int twa_reset_device_extension(TW_Device_Extension *tw_dev)
{
	int i = 0;
	int retval = 1;
	unsigned long flags = 0;

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TW_DISABLE_INTERRUPTS(tw_dev);
	TW_MASK_COMMAND_INTERRUPT(tw_dev);
	spin_lock_irqsave(tw_dev->host->host_lock, flags);

	/* Abort all requests that are in progress */
	for (i = 0; i < TW_Q_LENGTH; i++) {
		if ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) {
			if (tw_dev->srb[i]) {
				struct scsi_cmnd *cmd = tw_dev->srb[i];

				cmd->result = (DID_RESET << 16);
				if (twa_command_mapped(cmd))
					scsi_dma_unmap(cmd);
				cmd->scsi_done(cmd);
			}
		}
	}

	/* Reset queues and counts */
	for (i = 0; i < TW_Q_LENGTH; i++) {
		tw_dev->free_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	}
	tw_dev->free_head = TW_Q_START;
	tw_dev->free_tail = TW_Q_START;
	tw_dev->posted_request_count = 0;
	tw_dev->pending_request_count = 0;
	tw_dev->pending_head = TW_Q_START;
	tw_dev->pending_tail = TW_Q_START;
	tw_dev->reset_print = 0;

	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	if (twa_reset_sequence(tw_dev, 1))
		goto out;

	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);
	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	retval = 0;
out:
	return retval;
}