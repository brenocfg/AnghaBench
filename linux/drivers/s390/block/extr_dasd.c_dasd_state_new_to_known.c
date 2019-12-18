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
struct dasd_device {int /*<<< orphan*/  state; scalar_t__ block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STATE_KNOWN ; 
 int dasd_alloc_queue (scalar_t__) ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 

__attribute__((used)) static int dasd_state_new_to_known(struct dasd_device *device)
{
	int rc;

	/*
	 * As long as the device is not in state DASD_STATE_NEW we want to
	 * keep the reference count > 0.
	 */
	dasd_get_device(device);

	if (device->block) {
		rc = dasd_alloc_queue(device->block);
		if (rc) {
			dasd_put_device(device);
			return rc;
		}
	}
	device->state = DASD_STATE_KNOWN;
	return 0;
}