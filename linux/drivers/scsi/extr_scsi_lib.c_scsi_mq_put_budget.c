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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scsi_mq_put_budget(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;
	struct scsi_device *sdev = q->queuedata;

	atomic_dec(&sdev->device_busy);
}