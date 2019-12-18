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
struct scsi_device {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  request; scalar_t__ result; struct scsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_device_unbusy (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_set_blocked (struct scsi_cmnd*,int) ; 

__attribute__((used)) static void __scsi_queue_insert(struct scsi_cmnd *cmd, int reason, bool unbusy)
{
	struct scsi_device *device = cmd->device;

	SCSI_LOG_MLQUEUE(1, scmd_printk(KERN_INFO, cmd,
		"Inserting command %p into mlqueue\n", cmd));

	scsi_set_blocked(cmd, reason);

	/*
	 * Decrement the counters, since these commands are no longer
	 * active on the host/device.
	 */
	if (unbusy)
		scsi_device_unbusy(device);

	/*
	 * Requeue this command.  It will go before all other commands
	 * that are already in the queue. Schedule requeue work under
	 * lock such that the kblockd_schedule_work() call happens
	 * before blk_cleanup_queue() finishes.
	 */
	cmd->result = 0;

	blk_mq_requeue_request(cmd->request, true);
}