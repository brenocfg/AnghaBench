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
struct scsi_device {struct Scsi_Host* host; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue_num; struct request_queue* queue; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* commit_rqs ) (struct Scsi_Host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct Scsi_Host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_commit_rqs(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;
	struct scsi_device *sdev = q->queuedata;
	struct Scsi_Host *shost = sdev->host;

	shost->hostt->commit_rqs(shost, hctx->queue_num);
}