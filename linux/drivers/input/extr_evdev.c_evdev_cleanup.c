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
struct input_handle {int dummy; } ;
struct evdev {scalar_t__ open; struct input_handle handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdev_hangup (struct evdev*) ; 
 int /*<<< orphan*/  evdev_mark_dead (struct evdev*) ; 
 int /*<<< orphan*/  input_close_device (struct input_handle*) ; 
 int /*<<< orphan*/  input_flush_device (struct input_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void evdev_cleanup(struct evdev *evdev)
{
	struct input_handle *handle = &evdev->handle;

	evdev_mark_dead(evdev);
	evdev_hangup(evdev);

	/* evdev is marked dead so no one else accesses evdev->open */
	if (evdev->open) {
		input_flush_device(handle, NULL);
		input_close_device(handle);
	}
}