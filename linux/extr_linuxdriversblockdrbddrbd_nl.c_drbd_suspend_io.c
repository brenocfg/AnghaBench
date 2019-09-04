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
struct drbd_device {int /*<<< orphan*/  ap_bio_cnt; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  suspend_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ drbd_suspended (struct drbd_device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void drbd_suspend_io(struct drbd_device *device)
{
	atomic_inc(&device->suspend_cnt);
	if (drbd_suspended(device))
		return;
	wait_event(device->misc_wait, !atomic_read(&device->ap_bio_cnt));
}