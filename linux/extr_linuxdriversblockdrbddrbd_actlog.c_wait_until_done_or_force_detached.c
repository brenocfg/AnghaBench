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
struct drbd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  misc_wait; } ;
struct drbd_backing_dev {int /*<<< orphan*/  disk_conf; } ;
struct TYPE_2__ {long disk_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_FORCE_DETACH ; 
 int /*<<< orphan*/  FORCE_DETACH ; 
 long HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  drbd_chk_io_error (struct drbd_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,long) ; 

void wait_until_done_or_force_detached(struct drbd_device *device, struct drbd_backing_dev *bdev,
				     unsigned int *done)
{
	long dt;

	rcu_read_lock();
	dt = rcu_dereference(bdev->disk_conf)->disk_timeout;
	rcu_read_unlock();
	dt = dt * HZ / 10;
	if (dt == 0)
		dt = MAX_SCHEDULE_TIMEOUT;

	dt = wait_event_timeout(device->misc_wait,
			*done || test_bit(FORCE_DETACH, &device->flags), dt);
	if (dt == 0) {
		drbd_err(device, "meta-data IO operation timed out\n");
		drbd_chk_io_error(device, 1, DRBD_FORCE_DETACH);
	}
}