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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_BLOCK ; 
 int /*<<< orphan*/  SDEV_CREATED_BLOCK ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue_nowait (struct request_queue*) ; 
 int scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 

int scsi_internal_device_block_nowait(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	int err = 0;

	err = scsi_device_set_state(sdev, SDEV_BLOCK);
	if (err) {
		err = scsi_device_set_state(sdev, SDEV_CREATED_BLOCK);

		if (err)
			return err;
	}

	/* 
	 * The device has transitioned to SDEV_BLOCK.  Stop the
	 * block layer from calling the midlayer with this device's
	 * request queue. 
	 */
	blk_mq_quiesce_queue_nowait(q);
	return 0;
}