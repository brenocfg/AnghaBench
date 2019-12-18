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

/* Variables and functions */
 int /*<<< orphan*/  kbd_update_leds_helper (struct input_handle*,unsigned int*) ; 
 int /*<<< orphan*/  keyboard_tasklet ; 
 unsigned int ledstate ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kbd_start(struct input_handle *handle)
{
	tasklet_disable(&keyboard_tasklet);

	if (ledstate != -1U)
		kbd_update_leds_helper(handle, &ledstate);

	tasklet_enable(&keyboard_tasklet);
}