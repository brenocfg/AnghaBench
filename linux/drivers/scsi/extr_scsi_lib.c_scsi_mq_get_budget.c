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
struct scsi_device {int /*<<< orphan*/  device_busy; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_QUEUE_DELAY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_delay_run_hw_queue (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_dev_queue_ready (struct request_queue*,struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_blocked (struct scsi_device*) ; 

__attribute__((used)) static bool scsi_mq_get_budget(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;
	struct scsi_device *sdev = q->queuedata;

	if (scsi_dev_queue_ready(q, sdev))
		return true;

	if (atomic_read(&sdev->device_busy) == 0 && !scsi_device_blocked(sdev))
		blk_mq_delay_run_hw_queue(hctx, SCSI_QUEUE_DELAY);
	return false;
}