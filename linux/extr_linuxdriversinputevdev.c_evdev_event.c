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
struct input_value {unsigned int member_0; unsigned int member_1; int member_2; } ;
struct input_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdev_events (struct input_handle*,struct input_value*,int) ; 

__attribute__((used)) static void evdev_event(struct input_handle *handle,
			unsigned int type, unsigned int code, int value)
{
	struct input_value vals[] = { { type, code, value } };

	evdev_events(handle, vals, 1);
}