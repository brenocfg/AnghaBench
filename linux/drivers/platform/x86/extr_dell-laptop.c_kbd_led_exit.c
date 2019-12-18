#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  brightness_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  brightness_set_exit ; 
 TYPE_1__ kbd_led ; 
 int /*<<< orphan*/  kbd_led_present ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void kbd_led_exit(void)
{
	if (!kbd_led_present)
		return;
	kbd_led.brightness_set = brightness_set_exit;
	led_classdev_unregister(&kbd_led);
}