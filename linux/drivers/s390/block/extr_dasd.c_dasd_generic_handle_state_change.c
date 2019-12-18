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
struct dasd_device {TYPE_1__* block; } ;
struct TYPE_2__ {scalar_t__ request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (scalar_t__,int) ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_snss (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 

void dasd_generic_handle_state_change(struct dasd_device *device)
{
	/* First of all start sense subsystem status request. */
	dasd_eer_snss(device);

	dasd_device_remove_stop_bits(device, DASD_STOPPED_PENDING);
	dasd_schedule_device_bh(device);
	if (device->block) {
		dasd_schedule_block_bh(device->block);
		if (device->block->request_queue)
			blk_mq_run_hw_queues(device->block->request_queue,
					     true);
	}
}