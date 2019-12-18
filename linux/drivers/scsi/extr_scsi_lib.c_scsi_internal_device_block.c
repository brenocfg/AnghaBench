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
struct scsi_device {int /*<<< orphan*/  state_mutex; struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scsi_internal_device_block_nowait (struct scsi_device*) ; 

__attribute__((used)) static int scsi_internal_device_block(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	int err;

	mutex_lock(&sdev->state_mutex);
	err = scsi_internal_device_block_nowait(sdev);
	if (err == 0)
		blk_mq_quiesce_queue(q);
	mutex_unlock(&sdev->state_mutex);

	return err;
}