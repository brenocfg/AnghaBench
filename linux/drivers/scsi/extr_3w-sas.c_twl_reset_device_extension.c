#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_9__ {scalar_t__* state; int* free_queue; TYPE_4__* host; int /*<<< orphan*/  chrdev_request_id; int /*<<< orphan*/  flags; scalar_t__ posted_request_count; void* free_tail; void* free_head; struct scsi_cmnd** srb; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int DID_RESET ; 
 int /*<<< orphan*/  TWL_CLEAR_DB_INTERRUPT (TYPE_1__*) ; 
 int /*<<< orphan*/  TWL_MASK_INTERRUPTS (TYPE_1__*) ; 
 int /*<<< orphan*/  TWL_UNMASK_INTERRUPTS (TYPE_1__*) ; 
 int /*<<< orphan*/  TW_IN_RESET ; 
 int /*<<< orphan*/  TW_IOCTL_CHRDEV_FREE ; 
 int TW_Q_LENGTH ; 
 void* TW_Q_START ; 
 scalar_t__ TW_S_COMPLETED ; 
 scalar_t__ TW_S_FINISHED ; 
 scalar_t__ TW_S_INITIAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_block_requests (TYPE_4__*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ twl_reset_sequence (TYPE_1__*,int) ; 

__attribute__((used)) static int twl_reset_device_extension(TW_Device_Extension *tw_dev, int ioctl_reset)
{
	int i = 0, retval = 1;
	unsigned long flags = 0;

	/* Block SCSI requests while we are resetting */
	if (ioctl_reset)
		scsi_block_requests(tw_dev->host);

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TWL_MASK_INTERRUPTS(tw_dev);
	TWL_CLEAR_DB_INTERRUPT(tw_dev);

	spin_lock_irqsave(tw_dev->host->host_lock, flags);

	/* Abort all requests that are in progress */
	for (i = 0; i < TW_Q_LENGTH; i++) {
		if ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) {
			struct scsi_cmnd *cmd = tw_dev->srb[i];

			if (cmd) {
				cmd->result = (DID_RESET << 16);
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

	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	if (twl_reset_sequence(tw_dev, 1))
		goto out;

	TWL_UNMASK_INTERRUPTS(tw_dev);

	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	retval = 0;
out:
	if (ioctl_reset)
		scsi_unblock_requests(tw_dev->host);
	return retval;
}