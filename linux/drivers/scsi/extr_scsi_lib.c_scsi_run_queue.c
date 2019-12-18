#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {TYPE_2__* host; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct TYPE_4__ {int /*<<< orphan*/  starved_list; } ;
struct TYPE_3__ {scalar_t__ single_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_single_lun_run (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_starved_list_run (TYPE_2__*) ; 
 TYPE_1__* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static void scsi_run_queue(struct request_queue *q)
{
	struct scsi_device *sdev = q->queuedata;

	if (scsi_target(sdev)->single_lun)
		scsi_single_lun_run(sdev);
	if (!list_empty(&sdev->host->starved_list))
		scsi_starved_list_run(sdev->host);

	blk_mq_run_hw_queues(q, false);
}