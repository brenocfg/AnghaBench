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
struct joydev {scalar_t__ open; struct input_handle handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (struct input_handle*) ; 
 int /*<<< orphan*/  joydev_hangup (struct joydev*) ; 
 int /*<<< orphan*/  joydev_mark_dead (struct joydev*) ; 

__attribute__((used)) static void joydev_cleanup(struct joydev *joydev)
{
	struct input_handle *handle = &joydev->handle;

	joydev_mark_dead(joydev);
	joydev_hangup(joydev);

	/* joydev is marked dead so no one else accesses joydev->open */
	if (joydev->open)
		input_close_device(handle);
}