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
struct TYPE_4__ {char const* current_use; int /*<<< orphan*/  page; scalar_t__ start_jif; scalar_t__ submit_jif; int /*<<< orphan*/  in_use; } ;
struct TYPE_3__ {scalar_t__ disk; } ;
struct drbd_device {TYPE_2__ md_io; TYPE_1__ state; int /*<<< orphan*/  misc_wait; } ;

/* Variables and functions */
 scalar_t__ D_FAILED ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void *drbd_md_get_buffer(struct drbd_device *device, const char *intent)
{
	int r;

	wait_event(device->misc_wait,
		   (r = atomic_cmpxchg(&device->md_io.in_use, 0, 1)) == 0 ||
		   device->state.disk <= D_FAILED);

	if (r)
		return NULL;

	device->md_io.current_use = intent;
	device->md_io.start_jif = jiffies;
	device->md_io.submit_jif = device->md_io.start_jif - 1;
	return page_address(device->md_io.page);
}