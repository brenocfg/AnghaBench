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
struct dasd_device {int target; int state; int /*<<< orphan*/  state_mutex; } ;

/* Variables and functions */
 int DASD_STATE_READY ; 
 int /*<<< orphan*/  dasd_change_state (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_init_waitq ; 
 scalar_t__ dasd_probeonly ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dasd_set_target_state(struct dasd_device *device, int target)
{
	dasd_get_device(device);
	mutex_lock(&device->state_mutex);
	/* If we are in probeonly mode stop at DASD_STATE_READY. */
	if (dasd_probeonly && target > DASD_STATE_READY)
		target = DASD_STATE_READY;
	if (device->target != target) {
		if (device->state == target)
			wake_up(&dasd_init_waitq);
		device->target = target;
	}
	if (device->state != device->target)
		dasd_change_state(device);
	mutex_unlock(&device->state_mutex);
	dasd_put_device(device);
}