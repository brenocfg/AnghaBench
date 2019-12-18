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
struct dasd_device {int /*<<< orphan*/  stopped; TYPE_2__* block; TYPE_1__* cdev; } ;
struct TYPE_4__ {scalar_t__ request_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_NOSPC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (scalar_t__,int) ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (TYPE_2__*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  generic_waitq ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dasd_generic_space_avail(struct dasd_device *device)
{
	dev_info(&device->cdev->dev, "Extent pool space is available\n");
	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "space available");

	dasd_device_remove_stop_bits(device, DASD_STOPPED_NOSPC);
	dasd_schedule_device_bh(device);

	if (device->block) {
		dasd_schedule_block_bh(device->block);
		if (device->block->request_queue)
			blk_mq_run_hw_queues(device->block->request_queue, true);
	}
	if (!device->stopped)
		wake_up(&generic_waitq);
}