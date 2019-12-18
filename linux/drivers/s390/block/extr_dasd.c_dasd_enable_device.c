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
struct dasd_device {scalar_t__ state; TYPE_1__* discipline; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* kick_validate ) (struct dasd_device*) ;} ;

/* Variables and functions */
 scalar_t__ DASD_STATE_KNOWN ; 
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 int /*<<< orphan*/  DASD_STATE_ONLINE ; 
 int /*<<< orphan*/  _wait_for_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_init_waitq ; 
 int /*<<< orphan*/  dasd_reload_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dasd_enable_device(struct dasd_device *device)
{
	dasd_set_target_state(device, DASD_STATE_ONLINE);
	if (device->state <= DASD_STATE_KNOWN)
		/* No discipline for device found. */
		dasd_set_target_state(device, DASD_STATE_NEW);
	/* Now wait for the devices to come up. */
	wait_event(dasd_init_waitq, _wait_for_device(device));

	dasd_reload_device(device);
	if (device->discipline->kick_validate)
		device->discipline->kick_validate(device);
}