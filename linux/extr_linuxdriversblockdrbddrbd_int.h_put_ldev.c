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
struct TYPE_2__ {int disk; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  local_cnt; TYPE_1__ state; } ;
typedef  enum drbd_disk_state { ____Placeholder_drbd_disk_state } drbd_disk_state ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_DISK ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int D_DISKLESS ; 
 int D_FAILED ; 
 int /*<<< orphan*/  GOING_DISKLESS ; 
 int /*<<< orphan*/  GO_DISKLESS ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ ) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_device_post_work (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void put_ldev(struct drbd_device *device)
{
	enum drbd_disk_state disk_state = device->state.disk;
	/* We must check the state *before* the atomic_dec becomes visible,
	 * or we have a theoretical race where someone hitting zero,
	 * while state still D_FAILED, will then see D_DISKLESS in the
	 * condition below and calling into destroy, where he must not, yet. */
	int i = atomic_dec_return(&device->local_cnt);

	/* This may be called from some endio handler,
	 * so we must not sleep here. */

	__release(local);
	D_ASSERT(device, i >= 0);
	if (i == 0) {
		if (disk_state == D_DISKLESS)
			/* even internal references gone, safe to destroy */
			drbd_device_post_work(device, DESTROY_DISK);
		if (disk_state == D_FAILED)
			/* all application IO references gone. */
			if (!test_and_set_bit(GOING_DISKLESS, &device->flags))
				drbd_device_post_work(device, GO_DISKLESS);
		wake_up(&device->misc_wait);
	}
}