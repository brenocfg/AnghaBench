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
struct dasd_device {scalar_t__ state; int /*<<< orphan*/  kick_validate; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 scalar_t__ DASD_STATE_ONLINE ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_kick_validate_server(struct dasd_device *device)
{
	dasd_get_device(device);
	/* exit if device not online or in offline processing */
	if (test_bit(DASD_FLAG_OFFLINE, &device->flags) ||
	   device->state < DASD_STATE_ONLINE) {
		dasd_put_device(device);
		return;
	}
	/* queue call to do_validate_server to the kernel event daemon. */
	if (!schedule_work(&device->kick_validate))
		dasd_put_device(device);
}