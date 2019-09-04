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
struct TYPE_2__ {scalar_t__ conn; } ;
struct drbd_device {unsigned long* rs_mark_time; size_t rs_last_mark; unsigned long* rs_mark_left; TYPE_1__ state; } ;

/* Variables and functions */
 scalar_t__ C_PAUSED_SYNC_S ; 
 scalar_t__ C_PAUSED_SYNC_T ; 
 int DRBD_SYNC_MARKS ; 
 scalar_t__ DRBD_SYNC_MARK_STEP ; 
 unsigned long jiffies ; 
 scalar_t__ time_after_eq (unsigned long,scalar_t__) ; 

void drbd_advance_rs_marks(struct drbd_device *device, unsigned long still_to_go)
{
	unsigned long now = jiffies;
	unsigned long last = device->rs_mark_time[device->rs_last_mark];
	int next = (device->rs_last_mark + 1) % DRBD_SYNC_MARKS;
	if (time_after_eq(now, last + DRBD_SYNC_MARK_STEP)) {
		if (device->rs_mark_left[device->rs_last_mark] != still_to_go &&
		    device->state.conn != C_PAUSED_SYNC_T &&
		    device->state.conn != C_PAUSED_SYNC_S) {
			device->rs_mark_time[next] = now;
			device->rs_mark_left[next] = still_to_go;
			device->rs_last_mark = next;
		}
	}
}