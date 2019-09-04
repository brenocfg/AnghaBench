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
struct wacom_led {int held; int /*<<< orphan*/  trigger; } ;
struct wacom {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wacom_led* wacom_led_find (struct wacom*,int,int) ; 

__attribute__((used)) static void wacom_24hd_update_leds(struct wacom *wacom, int mask, int group)
{
	struct wacom_led *led;
	int i;
	bool updated = false;

	/*
	 * 24HD has LED group 1 to the left and LED group 0 to the right.
	 * So group 0 matches the second half of the buttons and thus the mask
	 * needs to be shifted.
	 */
	if (group == 0)
		mask >>= 8;

	for (i = 0; i < 3; i++) {
		led = wacom_led_find(wacom, group, i);
		if (!led) {
			hid_err(wacom->hdev, "can't find LED %d in group %d\n",
				i, group);
			continue;
		}
		if (!updated && mask & BIT(i)) {
			led->held = true;
			led_trigger_event(&led->trigger, LED_FULL);
		} else {
			led->held = false;
		}
	}
}